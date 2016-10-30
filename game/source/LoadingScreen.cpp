#include "LoadingScreen.h"
#include "World.h"
#include "SFML/Graphics/Color.hpp"
#include <iostream>


namespace TT {

	LoadingScreen *LoadingScreen::_instance = NULL;

	LoadingScreen *LoadingScreen::GetInstance()
	{
		if (!_instance)
			_instance = new LoadingScreen(500.0f);

		return _instance;
	}

	LoadingScreen::~LoadingScreen()
	{
		_instance = NULL;
	}

	LoadingScreen::LoadingScreen(float speed)
	{
		_speed = speed;
		rectangle.setFillColor(sf::Color(0, 0, 0, 255));
		_alpha = 255;
		fadingin = false;
		fadingout = false;
		isfinished = false;
	}

	void LoadingScreen::OnGUI(sf::RenderWindow *window)
	{
		sf::Vector2f size(((float)World::GetInstance()->GetWindow()->getSize().x), ((float)World::GetInstance()->GetWindow()->getSize().y));
		rectangle.setSize(size);
		rectangle.setOrigin((float)0.5*size.x, 0.5*size.y);

		Draw(window);
	}

	void LoadingScreen::Update(float timeStep)
	{
		if (_alpha <= 255.0 && fadingin)
		{
			_alpha += _speed *timeStep;
			rectangle.setFillColor(sf::Color(0, 0, 0, _alpha));
		}
		if (_alpha >= 0.0 && fadingout)
		{
			_alpha -= _speed *timeStep;
			rectangle.setFillColor(sf::Color(0, 0, 0, _alpha));
		}
		if (_alpha < 0.0 && fadingout)
		{
			fadingout = false;
			rectangle.setFillColor(sf::Color(0, 0, 0, 0));
		}
		if (_alpha > 255.0 && fadingin)
		{
			fadingin = false;
			isfinished = true;
		}

	}

	void LoadingScreen::Draw(sf::RenderWindow *window)
	{
		rectangle.setPosition(window->getView().getCenter());
		window->draw(rectangle);
	}

	bool LoadingScreen::Fadein()
	{
		if(fadingin == false && isfinished == false && fadingout == false)
		{
			isfinished = false;
			_alpha = 0;
			rectangle.setFillColor(sf::Color(0, 0, 0, 0));
			fadingin = true;
		}
		return isfinished;
	}

	void LoadingScreen::Fadeout()
	{
		if(fadingin == false && isfinished == false && fadingout == false)
		{
			_alpha = 255;
			rectangle.setFillColor(sf::Color(0, 0, 0, 255));
			fadingout = true;
		}
	}

	bool LoadingScreen::isLoading()
	{
		return (fadingin || fadingout);
	}

	bool LoadingScreen::isFinished()
	{
		return isfinished;

	}

	
}
