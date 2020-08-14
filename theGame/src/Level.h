#pragma once 

#include <graphics/layers/layer.h>
#include <graphics/Sprite.h>
#include "Random.h"
#include <iostream>
#include <graphics/layers/Group.h>

namespace game {
	class Level {
	private:
		Cygnus::graphics::Group *m_cubesGroup = new Cygnus::graphics::Group(Cygnus::maths::Mat4::identity());
		std::vector<Cygnus::graphics::Sprite*> m_cubes;
		int const mc_cubesNumber = 10;
		float const mc_scoreTime = 0.55f;
		float m_cubesSpeed = 6.0f, m_scoreTimer;
		int m_currentIndex, m_lastIndex;

		Cygnus::maths::Vec3 topPosition = { 25.0f, 8.0f, 0.0f };
		Cygnus::maths::Vec3 bottomPosition = { 25.0f, -8.0f, 0.0f };

		Cygnus::maths::Vec3 scale = { 1.5f, 10.0f, 0.0f };

		void createCubes();
		void cubesMove(float timeStep);
		void repositionCube();
		bool checkCollision(Cygnus::graphics::Sprite *s1, Cygnus::graphics::Sprite *s2, float rotation);
		Cygnus::maths::Vec4 cubesMultiColors(float timeStep, Cygnus::maths::Vec4 const &v);

	public:
		Level();
		~Level();
		void update(float timeStep);
		void addToLayer(Cygnus::graphics::Layer *layer);
		void reset();
		bool playerBtwCubes(Cygnus::graphics::Sprite *s);
		bool collideWithCube(Cygnus::graphics::Sprite *player, float rotation);
	};
}