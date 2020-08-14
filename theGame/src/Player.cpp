#include "Player.h"

namespace game {

	Player::Player(graphics::Shader *shader) {
		m_sprite = new graphics::Sprite(0, 0, 1.0f, 1.0f, new graphics::Texture("assets/spaceShip.png"));
		m_shader = shader;
		m_sprite->setColor(maths::Vec4(0.0f, 0.0f, 0.0f, 1.0f));

		m_particleSystem = new ParticleEffect(40);

		// Smoke
		m_smokeParticle.position = { 0.0f, 0.0f };
		m_smokeParticle.velocity = { -2.0f, 0.0f }; 
		m_smokeParticle.sizeBegin = 0.60f; 
		m_smokeParticle.sizeEnd = 0.0f; 
		m_smokeParticle.color = { 0.8f, 0.6f, 0.8f, 1.0f };
		m_smokeParticle.lifeTime = 4.0f;

		// Flames
		m_fireParticle.position = { 0.0f, 0.0f };
		m_fireParticle.velocity = { -2.0f, 0.0f }; 
		m_fireParticle.sizeBegin = 0.5f; 
		m_fireParticle.sizeEnd = 0.0f; 
		m_fireParticle.color = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
		m_fireParticle.lifeTime = 1.0f;
	}

	Player::~Player() {
		delete m_sprite;
	}

	void Player::move(float timeStep, bool keyPressed, Cygnus::graphics::Layer *layer) {

		if (keyPressed) {
			m_velocity -= mc_engine;
			angleRotation -= 150.0f * timeStep;

			if (m_pTimer <= 0) {
				spitFire = true;
				m_pTimer = 0.1f;
			}
			else {
				m_pTimer -= timeStep;
			}

			//m_fireParticle.velocity.y -= -m_velocity * 0.2f - 0.2f;

		}
		else {
			m_velocity += mc_gravity;
			angleRotation += 80.0f * timeStep;
		}
		
		float a = (DEFAULT_ROTATION - angleRotation) / DEFAULT_ROTATION;
		float aSign = maths::sign(a);

		m_velocity = std::clamp(m_velocity, -20.0f, 20.0f);
		angleRotation = std::clamp(angleRotation, 60.0f, 90.0f);
		m_position.x += m_velocity * timeStep;
		if (spitFire) {
			m_fireParticle.position = maths::Vec2(0.1f, -(m_position.x + (0.3f * -maths::sign(m_position.x))));
			m_particleSystem->emit(m_fireParticle, layer);
			spitFire = false;
		}

		if (smokeTimer <= 0) {
			m_smokeParticle.position = maths::Vec2(0.1f, -(m_position.x + (0.3f * -maths::sign(m_position.x))));
			m_particleSystem->emit(m_smokeParticle, layer);
			smokeTimer = timeSmoke;
		}
		else {
			smokeTimer -= timeStep;
		}

		a = m_position.x * a;

		m_sprite->setPosition(maths::Vec3(m_position.x + a * -aSign, m_position.y - a, -0.1f));
		m_sprite->setTransformationMatrix(maths::Mat4::rotation(angleRotation, maths::Vec3(0, 0, 1.0f)));

		m_particleSystem->update(timeStep);

	}

	void Player::reset() {
		m_position = { 0, 0 };
		m_velocity = 0;
		angleRotation = 90.0f;

	}


}