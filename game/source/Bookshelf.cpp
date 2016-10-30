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
		hidden = true;
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

		if(Bookshelf::_activeCounter == 5)
		{
			canInteract = false;
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

			if(_id == 4)
			{
				std::cout << "BAM!" << std::endl;
			}
		}
		else
		{
			Bookshelf::_activeCounter = 0;
		}
	}

	void Bookshelf::StartGlow()
	{
		if(_glow)
			return;

		if(_id == 0)
		{
			_glow = World::CreateSprite("assets/textures/level_3/puzzle_1.png");
			_glow->setPosition(352-960+42, 485-410+52);
		}
		if(_id == 1)
		{
			_glow = World::CreateSprite("assets/textures/level_3/puzzle_2.png");
			_glow->setPosition(802-960+47, 309-410+52);
		}
		if(_id == 2)
		{
			_glow = World::CreateSprite("assets/textures/level_3/puzzle_3.png");
			_glow->setPosition(1097-960+43, 638-410+44);
		}
		if(_id == 3)
		{
			_glow = World::CreateSprite("assets/textures/level_3/puzzle_4.png");
			_glow->setPosition(1466-960+58, 283-410+56);
		}
		if(_id == 4)
		{
			_glow = World::CreateSprite("assets/textures/level_3/puzzle_5.png");
			_glow->setPosition(1751-960+63, 413-410+66);
		}
	}

	void Bookshelf::StopGlow()
	{
		if(!_glow)
			return;

		delete _glow;
		_glow = nullptr;
	}
}
