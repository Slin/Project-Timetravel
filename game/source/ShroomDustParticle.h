//
// Created by Nils Daumann on 30.10.16.
//

#ifndef SHROOMDUSTPARTICLE_H
#define SHROOMDUSTPARTICLE_H

#include "Entity.h"

namespace TT
{
	class ParticleEmitter;
	class ShroomDustParticle : public sf::Sprite
	{
	public:
		ShroomDustParticle(ParticleEmitter *emitter);
		void Update(float timeStep);

		sf::Vector2f speed;

	private:
		ParticleEmitter *_emitter;
		float _alpha;
	};
}

#endif //SHROOMDUSTPARTICLE_H
