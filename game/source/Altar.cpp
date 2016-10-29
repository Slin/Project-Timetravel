//
// Created by Nils Daumann on 29.10.16.
//

#include "Altar.h"

namespace TT
{
	int Altar::_activeCounter = 0;

	Altar::Altar(int id, sf::Vector2f position) : Actor(position, "assets/textures/none.png", b2_kinematicBody, true), _id(id), _glow(nullptr)
	{
		if(World::KEYS[1])
		{
			StartGlow();
			Altar::_activeCounter = 3;
			canInteract = false;
		}
		else
		{
			canInteract = true;
		}

		hidden = true;
	}

	Altar::~Altar()
	{
		delete _glow;
	}

	void Altar::Update(float timeStep)
	{
		Actor::Update(timeStep);

		if(Altar::_activeCounter == 0 && canInteract)
		{
			StopGlow();
		}
	}

	void Altar::Draw(sf::RenderWindow *window)
	{
		Actor::Draw(window);

		if(_glow)
			window->draw(*_glow);
	}

	void Altar::OnBlur(Entity *interactor)
	{
		Actor::OnBlur(interactor);
		_spriteIndex = 0;
	}

	void Altar::OnFocus(Entity *interactor)
	{
		Actor::OnFocus(interactor);
		_spriteIndex = 1;
	}

	void Altar::OnInteract(Entity *interactor)
	{
		Actor::OnInteract(interactor);

		if(World::KEYS[1])
			return;

		if(_id == Altar::_activeCounter)
		{
			Altar::_activeCounter += 1;
			StartGlow();

			if(_id == 2)
			{
				World::KEYS[1] = true;
				canInteract = false;
			}
		}
		else
		{
			Altar::_activeCounter = 0;
		}
	}

	void Altar::StartGlow()
	{
		if(_glow)
			return;

		if(_id == 0)
			_glow = World::CreateSprite("assets/textures/level_2/glow1.png");
		if(_id == 2)
			_glow = World::CreateSprite("assets/textures/level_2/glow2.png");
		if(_id == 1)
			_glow = World::CreateSprite("assets/textures/level_2/glow3.png");

		_glow->setPosition(2450, 110);
	}

	void Altar::StopGlow()
	{
		if(!_glow)
			return;

		delete _glow;
		_glow = nullptr;
	}
}