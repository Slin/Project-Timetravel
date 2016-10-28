#include "Clouds.h"

namespace TT {

	Clouds::~Clouds()
	{
		Background::~Background();
	}

	Clouds::Clouds(float offsetspeed, float speed, const std::string path)
	{
		Background::Background(speed, path);
		_offset = 0.0f;
		offsetspeed = _offsetspeed;
	}

	void Clouds::Draw(sf::RenderWindow *window, float timeStep)
	{
		if (!_object)
		{
			return;
		}
		sf::Vector2f center;
		center = window->getView().getCenter();
		_offset += _offsetspeed * timeStep;
		_object->setPosition(center.x * GetSpeed() + _offset, 0.0f);
		window->draw(*_object);
		
	}





}