#pragma once 

#include <graphics/Sprite.h>
#include <graphics/Texture.h>
#include <algorithm>
#include "ParticleEffect.h"
#include <graphics/layers/layer.h>

namespace game {
	using namespace Cygnus;

	class Player {

	#define DEFAULT_ROTATION  90.0f

	private :
		const float mc_engine = 0.17f;
		const float mc_gravity = 0.09f;
		const float timeSmoke = 3.0f;

		graphics::Sprite *m_sprite;
		graphics::Shader *m_shader;
		maths::Vec2 m_position{ 0.0f, 0.0f };
		float angleRotation = 90.0f, m_velocity;
		float m_pTimer = 0.1f, smokeTimer = 0;
		bool spitFire = false;

		ParticleEffect *m_particleSystem;
		ParticleProps m_smokeParticle, m_fireParticle;
		
	public :
		Player(graphics::Shader *shader);
		~Player();

		void move(float timeStep, bool keyPressed, Cygnus::graphics::Layer *layer);
		void reset();

		inline graphics::Sprite *getSprite() const { return m_sprite; }
		inline float getRitation() const { return angleRotation; }

	};
}