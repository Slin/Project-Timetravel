//
// Created by Nils Daumann on 07.11.15.
//

#include "ParticleEmitter.h"

namespace TT
{
	ParticleEmitter::ParticleEmitter()
	{
		for(int i = 100; i > 0; i--)
		{
			Update(0.5f);
		}
	}

	ParticleEmitter::~ParticleEmitter()
	{
		for(ShroomDustParticle *particle : _particles)
		{
			delete particle;
		}
	}

	void ParticleEmitter::Update(float timeStep)
	{
		for(unsigned long i = _particles.size(); i < 100; i++)
		{
			_particles.push_back(new ShroomDustParticle(this));

			sf::Vector2f dir((rand()/(float)RAND_MAX)-0.5f, (rand()/(float)RAND_MAX)-0.5f);
			dir.x *= 3000;
			dir.x += 400;
			dir.y *= 50;
			dir.y += 250;
			_particles[i]->setPosition(dir);
			_particles[i]->speed = sf::Vector2f(0.0f, -(rand()/(float)RAND_MAX+1.0f)*10.0f);
		}

		for(ShroomDustParticle *particle : _particles)
		{
			particle->Update(timeStep);
		}

		for(ShroomDustParticle *particle : _particlesToRemove)
		{
			_particles.erase(std::find(_particles.begin(), _particles.end(), particle));
			delete particle;
		}
		_particlesToRemove.clear();
	}

	void ParticleEmitter::Draw(sf::RenderWindow *window)
	{
		for(ShroomDustParticle *particle : _particles)
		{
			sf::RenderStates renderStates = sf::RenderStates::Default;
			renderStates.blendMode = sf::BlendAdd;
			window->draw(*particle, renderStates);
		}
	}

	void ParticleEmitter::RemoveParticle(ShroomDustParticle *particle)
	{
		_particlesToRemove.push_back(particle);
	}
}
