//
// Created by Nils Daumann on 17.08.16.
//

#ifndef FANCYGOLDENLAMPS_PLAYERENTITY_H
#define FANCYGOLDENLAMPS_PLAYERENTITY_H

#include "World.h"

namespace TT
{
	class PlayerEntity : public Entity
	{
	public:

		PlayerEntity(int id, sf::Vector2f position);
		~PlayerEntity();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

		bool IsGrounded();

	private:
		sf::Sprite *_object;
		b2Body *_body;
		b2Fixture *_boxFixture;

		sf::Sound _sound;

		sf::Vector2f _spawnPosition;

		int _jumpTimer;

		float _animationTimer;
	};
}

#endif //FANCYGOLDENLAMPS_PLAYERENTITY_H
