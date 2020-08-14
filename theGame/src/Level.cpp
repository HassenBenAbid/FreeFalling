#include "Level.h"

namespace game {

	Level::Level(){
		createCubes();
		m_currentIndex = 0;
		m_lastIndex = mc_cubesNumber-1;
	}

	Level::~Level() {
		for (Cygnus::graphics::Sprite *sprite : m_cubes) {
			delete sprite;
		}


	}
		
	void Level::update(float timeStep) {
		cubesMove(timeStep);
		repositionCube();
		m_scoreTimer -= timeStep;
	}

	void Level::addToLayer(Cygnus::graphics::Layer *layer) {
		for (Cygnus::graphics::Sprite *cube : m_cubes) {
			cube->setColor(Cygnus::maths::Vec4(0, 0, 0, 1.0f));
			m_cubesGroup->add(cube);
		}

		layer->add(m_cubesGroup);
	}

	void Level::createCubes() {
		for (int i = 0; i < mc_cubesNumber; i+=2) {
			float yPosition = Random::isFloat() * 6.0f + 3.0f;
			float btw = Random::isFloat() * yPosition;
			m_cubes.push_back(new Cygnus::graphics::Sprite(topPosition.x + i * 3.5f, btw, scale.x, scale.y, Cygnus::maths::Vec4(0, 0, 0, 1.0f)));
			btw -= yPosition;
			m_cubes.push_back(new Cygnus::graphics::Sprite(bottomPosition.x + i * 3.5f, btw - scale.y, scale.x, scale.y, Cygnus::maths::Vec4(0, 0, 0, 1.0f)));
			
		}

	}

	void Level::cubesMove(float timestep) {

		Cygnus::maths::Vec4 newColor = cubesMultiColors(timestep, m_cubes[0]->getColor());

		for (Cygnus::graphics::Sprite *cube : m_cubes) {
			cube->moveXPosition(-m_cubesSpeed * timestep);
			cube->setColor(newColor);
		}
	}

	Cygnus::maths::Vec4 Level::cubesMultiColors(float timeStep, Cygnus::maths::Vec4 const &v) {
		float r = v.x;
		float g = v.y;
		float b = v.z;
	

		float speed = 0.5f;

		if (r == 1) {
			g >=1 ? g = 1 : g += speed * timeStep;
			b = 0;
		}
		if (g == 1) {
			b >= 1 ? b = 1 : b += speed * timeStep;
			r = 0;
		}
		if (b == 1) {
			r >= 1 ? r = 1 : r += speed * timeStep;
			g = 0;
		}
		else {
			r >= 1 ? r = 1 : r += speed * timeStep;
		}

		return Cygnus::maths::Vec4(r, g, b, 1.0f);
	}

	void Level::repositionCube() {
		if (m_cubes[m_currentIndex]->getPosition().x < -15.0f) {
			float lastPosition = m_cubes[m_lastIndex]->getPosition().x;
			float yPosition = Random::isFloat() * 6.0f + 3.0f;
			float btw = Random::isFloat() * yPosition;
			m_cubes[m_currentIndex]->setPosition(Cygnus::maths::Vec3(lastPosition + scale.x + 5.0f, btw, 0));
			btw -= yPosition;
			m_cubes[m_currentIndex + 1]->setPosition(Cygnus::maths::Vec3(lastPosition + scale.x + 5.0f, btw - scale.y, 0));

			m_lastIndex = m_currentIndex;
			m_currentIndex = (2 + m_currentIndex) % mc_cubesNumber;


		}
	}

	bool Level::checkCollision(Cygnus::graphics::Sprite *s1, Cygnus::graphics::Sprite *s2, float rotation) {


		Cygnus::maths::Vec3 pos = Cygnus::maths::Mat4::rotation(rotation, Cygnus::maths::Vec3(0, 0, 1.0f)) * s1->getPosition();
		
		bool collisionX = pos.x + s1->getSize().x >= s2->getPosition().x &&
			s2->getPosition().x + s2->getSize().x >= pos.x;

		bool collisionY = pos.y + s1->getSize().y + (0.80f * -Cygnus::maths::sign(s2->getPosition().y)) >= s2->getPosition().y &&
			s2->getPosition().y + s2->getSize().y >= pos.y + (0.80f * Cygnus::maths::sign(s2->getPosition().y));
		
		return collisionX && collisionY;
	}

	bool Level::collideWithCube(Cygnus::graphics::Sprite *player, float rotation) {
		for (Cygnus::graphics::Sprite *cube : m_cubes) {
			if (checkCollision(player, cube, rotation)) {
				return true;
			}
		}

		return false;
	}

	void Level::reset() {
		for (int i = 0; i < mc_cubesNumber; i += 2) {
			float yPosition = Random::isFloat() * 6.0f + 3.0f;
			float btw = Random::isFloat() * yPosition;
			m_cubes[i]->setPosition(Cygnus::maths::Vec3(topPosition.x + i * 3.5f, btw, 0));
			btw -= yPosition;
			m_cubes[i+1]->setPosition(Cygnus::maths::Vec3(bottomPosition.x + i * 3.5f, btw - scale.y, 0));
		}

		m_currentIndex = 0;
		m_lastIndex = mc_cubesNumber - 1;
	}

	bool Level::playerBtwCubes(Cygnus::graphics::Sprite *s) {

		if (m_scoreTimer <= 0) {
			for (int i = 0; i < mc_cubesNumber; i += 2) {
				if (m_cubes[i]->getPosition().x <= s->getPosition().x && m_cubes[i]->getPosition().x + scale.x >= s->getPosition().x) {
					m_scoreTimer = mc_scoreTime;
					return true;
				}
			}
		}

		return false;

	}

	
}