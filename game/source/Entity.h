//
// Created by Nils Daumann on 17.08.16.
//

#ifndef TIMETRAVEL_ENTITY_H
#define TIMETRAVEL_ENTITY_H

#include "EntityManager.h"
#include "World.h"
#include <SFML/Graphics.hpp>


namespace TT
{
	class Entity
	{
	public:
		Entity()
		{
			EntityManager::GetInstance()->AddEntity(this);
		}
		virtual ~Entity()
		{

		}

		virtual void Update(float timeStep) = 0;
		virtual void Draw(sf::RenderWindow *window) = 0;
		virtual void DrawLate(sf::RenderWindow *window)
		{

		}

		virtual void Interpolate(float factor)
		{
			_position = _position*factor + _previousPosition*(1.0f-factor);
		}

		sf::Vector2f _position;
		sf::Vector2f _previousPosition;
	};
}

#endif //TIMETRAVEL_ENTITY_H
