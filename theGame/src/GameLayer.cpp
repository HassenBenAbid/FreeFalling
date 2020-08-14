#include "GameLayer.h"

namespace game {

	GameLayer::GameLayer() {
		init();
	}

	void GameLayer::init() {
		window = new graphics::Window("don't Fall", WINDOW_WIDTH, WINDOW_HEIGHT);
		createCamera(WINDOW_WIDTH, WINDOW_HEIGHT);

		m_renderer = new graphics::StandardRenderer2D();

		m_shader = new graphics::Shader("../Cygnus-core/src/shaders/shaders.vert", "../Cygnus-core/src/shaders/shaders.frag");
		m_shader->enable();
		m_shader->setUniformMat4("pr_matrix", m_projectionMatrix);
		
		GLint texIds[] = {
			0, 1
		};

		m_shader->setUniform1iv("tex", texIds, 2);
		m_shader->setUniform1i("tex", 0);

		m_shader->disable();

		createParallax(3);
		m_currentParallaxIndex = m_parallaxSprites.size() - 1;

		m_player = new Player(m_shader);
		add(m_player->getSprite());

		m_level = new Level();
		m_level->addToLayer(this);



		Random::init();
	}

	void GameLayer::playerMove() {

		bool keyPressed = false;

		if (window->keyPressed(GLFW_KEY_SPACE)) {
			keyPressed = true;
		}

		m_player->move(m_deltaTime * 0.5f, keyPressed, this);
	}


	void GameLayer::update() {

		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window->getGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui::StyleColorsDark();

		while (!window->closed())
		{

			m_deltaTime = window->getDeltaTime();

			window->clear();

			draw();

			UI();

			if (m_gameState == 1) {
				moveParallax();
				m_level->update(m_deltaTime);
				playerMove();
				if (m_level->collideWithCube(m_player->getSprite(), m_player->getRitation())) {
					std::cout << "collision" << std::endl;
					m_gameState = gameover;
				}

				if (m_level->playerBtwCubes(m_player->getSprite())) {
					m_score++;
				}
			}

			window->update();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}


	void GameLayer::createCamera(unsigned int width, unsigned int height) {
		float aspectRatio = (float)width / (float)height;

		float cameraWidth = 8.0f;
		float bottom = -cameraWidth;
		float top = cameraWidth;
		float left = bottom * aspectRatio;
		float right = top * aspectRatio;

		m_projectionMatrix = maths::Mat4::orthographic(left, right, bottom, top, -1.0f, 1.0f);
	}

	void GameLayer::gameoverMenu() {

		auto pos = ImGui::GetWindowPos();
		pos.x += WINDOW_WIDTH * 0.5f - 200.0f;
		pos.y += 50.0f;

		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 23.0f, pos, 0xff0000ff, "Another one bites the dust!");

		pos.x += WINDOW_WIDTH * 0.5f - 310.0f;
		pos.y += 50.0f;

		std::string scoreString = "Your score: " + std::to_string(m_score);
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 23.0f, pos, 0xff0000ff, scoreString.c_str());

		pos.x -= 30.0f;
		pos.y += 40.0f;
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 25.0f, pos, 0xffffffff, "CLICK TO RESTART");

		if (window->buttonPressed(GLFW_MOUSE_BUTTON_1)) {
			reset();
		}


	}

	void GameLayer::mainMenu() {

		auto pos = ImGui::GetWindowPos();
		pos.x += WINDOW_WIDTH * 0.5f - 200.0f;
		pos.y += 50.0f;

		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 25.0f, pos, 0xffffffff, "Press \"SPACE\" to start");

		pos.x += WINDOW_WIDTH * 0.5f - 380.0f;
		pos.y += 60.0f;

		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 22.0f, pos, 0xffffffff, "Press \"ESCAPE\" to quit");

		if (window->keyPressed(GLFW_KEY_SPACE)) {
			m_gameState = play;
		}
		else if (window->keyPressed(GLFW_KEY_ESCAPE)) {
			window->closeWindow();
		}
	}

	void GameLayer::UI() {

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (m_gameState == 0) {
			mainMenu();
		}
		else if (m_gameState == 1) {
			playingInterface();
		}
		else if (m_gameState == 2) {
			gameoverMenu();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GameLayer::playingInterface() {

		auto pos = ImGui::GetWindowPos();
		pos.x += WINDOW_WIDTH * 0.5f - 50.0f;
		pos.y = 30.0f;

		std::string stringScore = std::to_string(m_score);
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 20.0f, pos, 0xffffffff, stringScore.c_str());
	}

	void GameLayer::reset() {
		m_level->reset();
		m_player->reset();
		m_score = 0;
		m_gameState = play;
	}
	void GameLayer::createParallax(int size) {
		graphics::Texture *tex = new graphics::Texture("assets/space.png");
		float lastSize = 0;
		for (int i = 0; i < size; i++) {
			m_parallaxSprites.push_back(new graphics::Sprite(-14.0f + lastSize, -8.0f, 28.0f, 16.5f, tex));
			m_parallaxSprites[i]->setColor(maths::Vec4(0.0, 0.0, 0.0, 1.0f));
			m_parallaxSprites[i]->setPosition(maths::Vec3(m_parallaxSprites[i]->getPosition().x, m_parallaxSprites[i]->getPosition().y, -0.7));
			add(m_parallaxSprites[i]);
			lastSize = 28.0f + lastSize;
		}
		//add(parallaxGroup);
	}

	void GameLayer::moveParallax() {
		int index = 0;
		for (graphics::Sprite *spriteP : m_parallaxSprites) {
			spriteP->moveXPosition(-6.0f * m_deltaTime);
			if (spriteP->getPosition().x + spriteP->getSize().x <= -14.0f) {
				spriteP->setXPosition(m_parallaxSprites[m_currentParallaxIndex]->getPosition().x + m_parallaxSprites[m_currentParallaxIndex]->getSize().x - 0.7f);
				m_currentParallaxIndex = index;
			}
			index++;
		}
	}
}