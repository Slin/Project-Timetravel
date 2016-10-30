#include "Clouds.h"
#include <iostream>
namespace TT {

	Clouds::~Clouds()
	{
	}

	Clouds::Clouds(float offsetspeed, float speed, const std::string path) : Background(speed, path), _offset(0.0f), _offsetspeed(offsetspeed)
	{
		_object->setOrigin(0.0, _object->getOrigin().y);
		xproblematic = 0.0f;
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
		if (_offset > 5757.0f) _offset = 0;
		_object->setPosition(center.x * GetSpeed() + _offset, 0.0f);
		xproblematic = _object->getPosition().x;
		window->draw(*_object);
		_object->setPosition(xproblematic -5757.0, 0.0f);
		window->draw(*_object);
	}

	void Clouds::Update(float timeStep)
	{
		_offset += _offsetspeed * timeStep;
	}
}