//
// Created by Nils Daumann on 30.10.16.
//

#include "ShroomDustParticle.h"
#include "ParticleEmitter.h"
#include "PlayerEntity.h"
#include "Math.h"

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
		PlayerEntity *player = World::GetInstance()->GetPlayer();
		if(player)
		{
			float dist = Math::distance(player->_position, getPosition());
			if(dist < 1000)
			{
				_impulse = Math::sub(getPosition(), player->_position);
				if(_impulse.y > 0.0f)
				{
					_impulse.y = 0.0f;
				}
				_impulse /= Math::length(_impulse);
				_impulse *= (1.0f-dist/1000.0f)*40.0f;
			}
		}

		move(_impulse*timeStep);
		move(speed*timeStep);

		_impulse *= 1.0f-10.0f*timeStep;

		_alpha -= timeStep*7.0f;

		setColor(sf::Color(255, 255, 255, _alpha));

		if(_alpha < 0.0f)
		{
			_emitter->RemoveParticle(this);
		}
	}
}
