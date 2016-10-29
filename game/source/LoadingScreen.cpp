#include "LoadingScreen.h"
#include "World.h"
#include "SFML\Graphics\Color.hpp"
#include <iostream>


namespace TT {
	LoadingScreen::LoadingScreen(float speed)
	{
		_speed = speed;
		sf::Vector2f size(((float)World::GetInstance()->GetWindow()->getSize().x), ((float)World::GetInstance()->GetWindow()->getSize().y));
		rectangle.setSize(size);
		rectangle.setOrigin((float)0.5*size.x, 0.5*size.y);
		rectangle.setFillColor(sf::Color(0, 0, 0, 0));
		_alpha = 0;
		fadingin = true;
		fadingout = false;
	}

	void LoadingScreen::OnGUI(sf::RenderWindow *window)
	{
		Draw(window);
	}

	void LoadingScreen::Update(float timeStep)
	{
		if (_alpha < 255 && fadingin)
		{
			_alpha += _speed *timeStep;
			rectangle.setFillColor(sf::Color(0, 0, 0, 0 + _alpha));
		}
		if (_alpha > 0 && fadingout)
		{
			_alpha -= _speed *timeStep;
			rectangle.setFillColor(sf::Color(0, 0, 0, 0 + _alpha));
		}
	}

	void LoadingScreen::Draw(sf::RenderWindow *window)
	{
		rectangle.setPosition(window->getView().getCenter());
		window->draw(rectangle);
	}

	void LoadingScreen::Fadein(float timeStep)
	{
		fadingin = true;
	}

	void LoadingScreen::Fadeout(float timeStep)
	{
		fadingout = true;
	}
}
