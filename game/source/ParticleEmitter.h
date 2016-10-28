//
// Created by Nils Daumann on 07.11.15.
//

#ifndef TIMETRAVEL_PARTICLEEMITTER_H
#define TIMETRAVEL_PARTICLEEMITTER_H

#include "Entity.h"
//#include "BloodParticle.h"

namespace TT
{
	class ParticleEmitter : Entity
	{
	public:
		ParticleEmitter();
		~ParticleEmitter();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);
		void DrawLate(sf::RenderWindow *window);

		void Bleed();

	private:
//		BloodParticle *_particles[10000];
		int _currentParticle;
	};
}

#endif //TIMETRAVEL_PARTICLEEMITTER_H
