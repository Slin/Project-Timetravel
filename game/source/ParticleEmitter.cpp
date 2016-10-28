//
// Created by Nils Daumann on 07.11.15.
//

#include "ParticleEmitter.h"

namespace TT
{
	ParticleEmitter::ParticleEmitter()
	{
		_currentParticle = 0;
//		memset(_particles, 0, sizeof(_particles));
	}

	ParticleEmitter::~ParticleEmitter()
	{

	}

/*	void ParticleEmitter::Bleed()
	{
		for(int i = 0; i < 1000; i++)
		{
			_particles[_currentParticle] = new BloodParticle();
			_particles[_currentParticle]->setPosition(World::GetInstance()->GetWindow()->getSize().x*0.5f, 550.0f*World::GetInstance()->GetScaleFactor());

			sf::Vector2f dir((rand()/(float)RAND_MAX)-0.5f, -(rand()/(float)RAND_MAX)-0.5f);
			float length = sqrt(dir.x*dir.x+dir.y*dir.y);
			dir *= length*5.0f*((rand()/(float)RAND_MAX)*0.5f + 0.5f);
			_particles[_currentParticle]->speed = dir;

			_currentParticle += 1;
			if(_currentParticle >= 10000)
				_currentParticle = 0;
		}
	}*/

	void ParticleEmitter::Update(float timeStep)
	{
/*		for(int i = 0; i < 10000; i++)
		{
			if(!_particles[i])
				continue;

			_particles[i]->Update(timeStep);
		}*/
	}

	void ParticleEmitter::Draw(sf::RenderWindow *window)
	{

	}

	void ParticleEmitter::DrawLate(sf::RenderWindow *window)
	{
//		for(int i = 0; i < 10000; i++)
		{
/*			if(!_particles[i])
				continue;

			window->draw(*_particles[i]);*/
		}
	}
}
