#include "Clouds.h"
#include <iostream>
namespace TT {

	Clouds::~Clouds()
	{

	}

	Clouds::Clouds(float offsetspeed, float speed, const std::string path) : Background(speed, path), _offset(0.0f), _offsetspeed(offsetspeed)
	{
		
	}

	void Clouds::Draw(sf::RenderWindow *window)
	{
		if (!_object)
		{
			return;
		}

		sf::Vector2f center;
		center = window->getView().getCenter();
		float width = (float)window->getSize().x;

		if (_object->getPosition().x > center.x + width)
		{
			_object->setPosition(center.x - width, 0.0f);
			_offset = 0.0f;
		}

		_object->setPosition((center.x - 0.7*width) * GetSpeed() + _offset, 0.0f);
		
		window->draw(*_object);
	}

	void Clouds::Update(float timeStep)
	{
		_offset += _offsetspeed * timeStep;
	}
}