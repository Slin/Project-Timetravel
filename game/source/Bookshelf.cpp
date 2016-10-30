//
// Created by Nils Daumann on 30.10.16.
//

#include "Bookshelf.h"
#include <iostream>

namespace TT
{
	int Bookshelf::_activeCounter = 0;

	Bookshelf::Bookshelf(int id, sf::Vector2f position) : Actor(position, "assets/textures/none.png", b2_kinematicBody, true), _id(id), _glow(nullptr)
	{
		canInteract = true;
		hidden = false;
	}

	Bookshelf::~Bookshelf()
	{
		delete _glow;
	}

	void Bookshelf::Update(float timeStep)
	{
		Actor::Update(timeStep);

		if(Bookshelf::_activeCounter == 0 && canInteract)
		{
			StopGlow();
		}
	}

	void Bookshelf::Draw(sf::RenderWindow *window)
	{
		Actor::Draw(window);

		if(_glow)
			window->draw(*_glow);
	}

	void Bookshelf::OnBlur(Entity *interactor)
	{
		Actor::OnBlur(interactor);
		_spriteIndex = 0;
	}

	void Bookshelf::OnFocus(Entity *interactor)
	{
		Actor::OnFocus(interactor);
		_spriteIndex = 1;
	}

	void Bookshelf::OnInteract(Entity *interactor)
	{
		Actor::OnInteract(interactor);

		if(_id == Bookshelf::_activeCounter)
		{
			Bookshelf::_activeCounter += 1;
			StartGlow();

			std::cout << "Yo!" << std::endl;

			if(_id == 4)
			{
				std::cout << "BAM!" << std::endl;
				canInteract = false;
			}
		}
		else
		{
			std::cout << "NOOOO!" << std::endl;
			Bookshelf::_activeCounter = 0;
		}
	}

	void Bookshelf::StartGlow()
	{
		if(_glow)
			return;

/*		if(_id == 0)
			_glow = World::CreateSprite("assets/textures/level_3/glow1.png");
		if(_id == 2)
			_glow = World::CreateSprite("assets/textures/level_3/glow2.png");
		if(_id == 1)
			_glow = World::CreateSprite("assets/textures/level_3/glow3.png");

		_glow->setPosition(2450, 110);*/
	}

	void Bookshelf::StopGlow()
	{
		if(!_glow)
			return;

		delete _glow;
		_glow = nullptr;
	}
}
