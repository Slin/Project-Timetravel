//
// Created by Nils Daumann on 29.10.16.
//

#include "Altar.h"

namespace TT
{
	Altar::Altar(int id, sf::Vector2f position) : Actor(position, "assets/textures/none.png", b2_kinematicBody, true), _id(id)
	{
		canInteract = true;
	}

	Altar::~Altar()
	{

	}

	void Altar::Update(float timeStep)
	{
		Actor::Update(timeStep);
	}

	void Altar::Draw(sf::RenderWindow *window)
	{
		Actor::Draw(window);
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

		if(!World::GetInstance()->SelectPuzzlePiece(_id))
		{
			_spriteIndex = 0;
		}
	}

	void Altar::StartGlow()
	{

	}
}