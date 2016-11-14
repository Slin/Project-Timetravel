#include "Clouds.h"
#include <iostream>
namespace TT {

	Clouds::~Clouds()
	{
	}

	Clouds::Clouds(float offsetspeed, float speed, const std::vector<std::string> &paths) : Background(speed, paths), _offset(0.0f), _offsetspeed(offsetspeed)
	{
		float offset = 0;
		for(sf::Sprite *object : _objects)
		{
			object->setOrigin(-offset, object->getOrigin().y);
			offset += object->getGlobalBounds().width;
		}
		
		_maxOffset = offset;
	}

	void Clouds::Draw(sf::RenderWindow *window)
	{
		if(_objects.size() == 0)
		{
			return;
		}
		
		if(_offset > _maxOffset) _offset -= _maxOffset;
		float totalOffset = window->getView().getCenter().x*GetSpeed() + _offset;
		
		for(sf::Sprite *object : _objects)
		{
			object->setPosition(totalOffset, 0.0f);
			window->draw(*object);
			object->setPosition(totalOffset - _maxOffset, 0.0f);
			window->draw(*object);
		}
	}

	void Clouds::Update(float timeStep)
	{
		_offset += _offsetspeed * timeStep;
	}
}
