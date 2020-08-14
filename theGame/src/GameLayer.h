#pragma once 

#include <graphics/layers/layer.h>
#include <graphics/standardRenderer2D.h>
#include <graphics/window.h>
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_glfw.h"
#include "../Imgui/imgui_impl_opengl3.h"
#include "Player.h"
#include "Level.h"
#include "Random.h"


namespace game {
	using namespace Cygnus;

	class GameLayer : graphics::Layer {
	private:
		unsigned int const WINDOW_WIDTH = 800;
		unsigned int const WINDOW_HEIGHT = 480;

		enum GameState {
			mainmenu = 0,
			play = 1,
			gameover = 2
		};

		graphics::Window *window;
		Player *m_player;
		graphics::Group *m_parallaxGroup;
		Level *m_level;
		float m_deltaTime;
		GameState m_gameState = mainmenu;
		int m_score = 0, m_currentParallaxIndex;
		std::vector<Cygnus::graphics::Sprite*> m_parallaxSprites;

		void init();
		void playerMove();
		void gameoverMenu();
		void mainMenu();
		void playingInterface();
		void reset();
		void UI();
		void createParallax(int size);
		void moveParallax();

	public:
		GameLayer();
		void update();
		void createCamera(unsigned int width, unsigned int height);

	};
}