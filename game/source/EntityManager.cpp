//
// Created by Nils Daumann on 17.08.16.
//

#include "EntityManager.h"
#include "Entity.h"

namespace TT
{
	EntityManager *EntityManager::_instance = NULL;

	EntityManager* EntityManager::GetInstance()
	{
		if(!_instance)
			_instance = new EntityManager();

		return _instance;
	}

	EntityManager::EntityManager()
	{

	}

	void EntityManager::RemoveAllEntities()
	{
		for(Entity *entity : _entities)
		{
			delete entity;
		}
		_entities.clear();
		_entitiesToRemove.clear();
		_entitiesToAdd.clear();
	}

	void EntityManager::Interpolate(float factor)
	{
		for(Entity *entity:_entities)
		{
			entity->Interpolate(factor);
		}
	}

	void EntityManager::Draw(sf::RenderWindow *window)
	{
		//draw entities
		for(Entity *entity:_entities)
		{
			entity->Draw(window);
		}

		for(Entity *entity:_entities)
		{
			entity->DrawLate(window);
		}
	}

	void EntityManager::RemoveEntity(TT::Entity *entity)
	{
		if(entity)
		{
			_entitiesToRemove.push_front(entity);
		}
	}

	void EntityManager::AddEntity(TT::Entity *entity)
	{
		if(entity)
		{
			_entitiesToAdd.push_back(entity);
		}
	}

	void EntityManager::Update(float timeStep)
	{
		//add queued entities
		for(Entity *entity:_entitiesToAdd)
		{
			_entities.push_back(entity);
		}
		_entitiesToAdd.clear();

		//update entities
		for(Entity *entity:_entities)
		{
			entity->Update(timeStep);
		}

		//remove queued entities
		for(Entity *entity:_entitiesToRemove)
		{
			_entities.remove(entity);
		}
		_entitiesToRemove.clear();
	}
}