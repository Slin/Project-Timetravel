//
// Created by Nils Daumann on 17.08.16.
//

#ifndef TIMETRAVEL_PLAYERENTITY_H
#define TIMETRAVEL_PLAYERENTITY_H

#include "World.h"

namespace TT
{
	class PlayerEntity : public Entity
	{
	public:

		PlayerEntity(sf::Vector2f position);
		~PlayerEntity();

		void Update(float timeStep);
		void Interpolate(float factor);
		void Draw(sf::RenderWindow *window);

		bool IsGrounded();

	private:
		sf::Sprite *_object;
		b2Body *_body;
		b2Fixture *_boxFixture;

		sf::Sound _sound;

		float _animationTimer;
	};
}

#endif //TIMETRAVEL_PLAYERENTITY_H
