#include "Background.h"

namespace TT
{
	Background::Background()
	{
		
	}
	
	Background::Background(float speed, const std::string path) : _speed(speed)
	{
		sf::Sprite *object = World::CreateSprite(path);
		object->setOrigin(0.5f*World::GetInstance()->GetView()->getSize().x, object->getLocalBounds().height*0.5f);
		_objects.push_back(object);
	}
	
	Background::Background(float speed, const std::vector<std::string> &paths) : _speed(speed)
	{
		float offset = 0;
		for(std::string path : paths)
		{
			sf::Sprite *object = World::CreateSprite(path);
			object->setOrigin(0.5f*World::GetInstance()->GetView()->getSize().x-offset, object->getLocalBounds().height*0.5f);
			_objects.push_back(object);
			
			offset += object->getGlobalBounds().width;
		}
	}

	Background::~Background()
	{
		for(sf::Sprite *object : _objects)
		{
			delete object;
		}
	}

	void Background::Draw(sf::RenderWindow *window)
	{
		if(_objects.size() == 0)
		{
			return;
		}

		sf::Vector2f center;
		center = window->getView().getCenter();
		for(sf::Sprite *object : _objects)
		{
			object->setPosition(center.x * GetSpeed(), 0.0f);
			window->draw(*object);
		}
	}

	void Background::Update(float timeStep)
	{

	}
}
