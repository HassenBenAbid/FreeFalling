#include "ParticleEffect.h"

namespace game {

	ParticleEffect::ParticleEffect(int size) {
		m_particles.resize(size);
	}

	void ParticleEffect::emit(ParticleProps const &particleP, Cygnus::graphics::Layer *layer) {

		if (m_particles[m_particlesIndex] == nullptr) {
			m_particles[m_particlesIndex] = new aParticle;
			m_particles[m_particlesIndex]->cube = new Cygnus::graphics::Sprite(particleP.position.x, particleP.position.y, particleP.sizeBegin, particleP.sizeBegin, particleP.color);
			layer->add(m_particles[m_particlesIndex]->cube);
		}
		else {
			m_particles[m_particlesIndex]->cube->setPosition(Cygnus::maths::Vec3(particleP.position.x, particleP.position.y, -0.5));
			m_particles[m_particlesIndex]->cube->setColor(particleP.color);
			m_particles[m_particlesIndex]->cube->setSize(Cygnus::maths::Vec2(particleP.sizeBegin, particleP.sizeBegin));
		}


		m_particles[m_particlesIndex]->lifeRemaining = particleP.lifeTime;
		m_particles[m_particlesIndex]->color = particleP.color;
		m_particles[m_particlesIndex]->position = particleP.position;
		m_particles[m_particlesIndex]->velocity = particleP.velocity;
		m_particles[m_particlesIndex]->lifeTime = particleP.lifeTime;
		m_particles[m_particlesIndex]->sizeBegin = particleP.sizeBegin;
		m_particles[m_particlesIndex]->sizeEnd = particleP.sizeEnd;

		m_particlesIndex = ++m_particlesIndex % m_particles.size();
	}

	void ParticleEffect::update(float timeStep) {
		for (aParticle *particle : m_particles) {

			if (particle == nullptr || particle->lifeRemaining <= 0) {
				continue;	
			}
		
			particle->lifeRemaining -= timeStep;
			particle->position += particle->velocity * timeStep;
			particle->rotation += 50.0f * timeStep;

			float life = particle->lifeRemaining / particle->lifeTime;
			particle->color.w = life;

			float size = Cygnus::maths::lerp(particle->sizeEnd, particle->sizeBegin, life);
			particle->cube->setPosition(Cygnus::maths::Vec3(particle->position.x, particle->position.y, -0.5));
			particle->cube->setColor(particle->color);
			particle->cube->setSize(Cygnus::maths::Vec2(size, size));
			
			
		}
	}
}