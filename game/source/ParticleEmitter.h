//
// Created by Nils Daumann on 07.11.15.
//

#ifndef TIMETRAVEL_PARTICLEEMITTER_H
#define TIMETRAVEL_PARTICLEEMITTER_H

#include "Entity.h"
#include "ShroomDustParticle.h"

namespace TT
{
	class ParticleEmitter : Entity
	{
	public:
		ParticleEmitter();
		~ParticleEmitter();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

		void RemoveParticle(ShroomDustParticle *particle);

	private:
		std::vector<ShroomDustParticle*> _particles;
		std::vector<ShroomDustParticle*> _particlesToRemove;
	};
}

#endif //TIMETRAVEL_PARTICLEEMITTER_H
