//
// Created by Nils Daumann on 30.10.16.
//

#include "ShroomDustParticle.h"
#include "ParticleEmitter.h"

namespace TT
{
	ShroomDustParticle::ShroomDustParticle(ParticleEmitter *emitter) : _emitter(emitter)
	{
		sf::Texture *pTexture = TexturePool::GetInstance()->GetTexture("assets/textures/level_2/shroomdust.png");
		setTexture(*pTexture);

		setOrigin(getLocalBounds().width*0.5f, getLocalBounds().height*0.5f);
		setScale(1.0f, 1.0f);

		_alpha = (rand()/(float)RAND_MAX)*80.0f+100.0f;
	}

	void ShroomDustParticle::Update(float timeStep)
	{
		move(speed*timeStep);

		_alpha -= timeStep*7.0f;

		setColor(sf::Color(255, 255, 255, _alpha));

		if(_alpha < 0.0f)
		{
			_emitter->RemoveParticle(this);
		}
	}
}
