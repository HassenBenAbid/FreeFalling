#pragma once

#include <maths/maths.h>
#include "Random.h"
#include <graphics/layers/layer.h>
#include <graphics/Sprite.h>

namespace game {

	struct ParticleProps {
		Cygnus::maths::Vec2 position;
		Cygnus::maths::Vec2 velocity;
		Cygnus::maths::Vec4 color;
		float sizeBegin, sizeEnd;
		float lifeTime = 1.0f;
	};
	
	class ParticleEffect {
	private:

		struct aParticle
		{

			Cygnus::graphics::Sprite *cube = nullptr;
			Cygnus::maths::Vec2 position;
			Cygnus::maths::Vec4 color;
			Cygnus::maths::Vec2 velocity;

			float lifeRemaining = 1.0f;
			float lifeTime = 1.0f;
			float rotation = 0;
			float sizeBegin, sizeEnd;
		};

		std::vector<aParticle *> m_particles;
		unsigned int m_particlesIndex = 0;

	public:
		ParticleEffect(int size);

		void emit(ParticleProps const &particleP, Cygnus::graphics::Layer *layer);
		void update(float timeStep);


	};
}


