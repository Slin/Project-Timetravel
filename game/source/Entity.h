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
			EntityManager::GetInstance()->RemoveEntity(this);
		}

		virtual void Update(float timeStep) = 0;
		virtual void Draw(sf::RenderWindow *window) = 0;
		virtual void DrawLate(sf::RenderWindow *window)
		{

		}
	};
}

#endif //TIMETRAVEL_ENTITY_H
