//
// Created by Nils Daumann on 17.08.16.
//

#include "World.h"
#include "PlayerEntity.h"

#if __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

#define FULLSCREEN

namespace TT
{
	World *World::_instance = nullptr;

	World *World::GetInstance()
	{
		if(!_instance)
		{
			_instance = new World();
		}

		return _instance;
	}

	World::World() : _physicsWorld(nullptr)
	{
#if __APPLE__ && !(TARGET_OS_IPHONE) && NDEBUG
		CFBundleRef bundle = CFBundleGetMainBundle();
		CFURLRef url = CFBundleCopyBundleURL(bundle);

		CFStringRef urlString = CFURLCopyPath(url);

		const char *file = CFStringGetCStringPtr(urlString, kCFStringEncodingUTF8);
		_bundlePath = file;
		_bundlePath += "Contents/Resources/";
#else
		_bundlePath = "";
#endif

#if defined(FULLSCREEN)
		_window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Timetravel", sf::Style::Default);
#else
		_window = new sf::RenderWindow(sf::VideoMode(1920, 1200), "Fancy Golden Lamps");
#endif
		_window->setFramerateLimit(60);

		_view = new sf::View(sf::FloatRect(0.0f, -0.5*_window->getSize().y, _window->getSize().x, _window->getSize().y));
		// _view->zoom(1200.0f/_window->getSize().y);
		_window->setView(*_view);
		_window->clear(sf::Color::Black);
	}

	void World::LoadLevel()
	{
		Reset();
		new PlayerEntity(0, sf::Vector2f(32.0f, -100.0f));
		CreateStaticBoxCollider(sf::Vector2f(0.0f, 0.0f), sf::Vector2u(1000, 10));
	}

	void World::Reset()
	{
		EntityManager::GetInstance()->RemoveAllEntities();

		if(_physicsWorld)
			delete _physicsWorld;

		b2Vec2 gravity(0.0f, 9.81f);
		_physicsWorld = new b2World(gravity);
	}

	void World::Loop()
	{
		LoadLevel();

		sf::Clock clock;
		sf::Time deltaTime;
		sf::Time time = sf::Time::Zero;

		while(_window->isOpen())
		{
			sf::Event event;
			while(_window->pollEvent(event))
			{
				if(event.type == sf::Event::Closed)
				{
					_window->close();
				}
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				_window->close();
				break;
			}

			deltaTime = clock.getElapsedTime();
			time += deltaTime;
			clock.restart();
			int counter = 0;
			while(time.asSeconds() > 1.0f / 60.0f && counter < 10)
			{
				_physicsWorld->Step(1.0f / 60.0f, 10, 5);

				EntityManager::GetInstance()->Update(1.0f / 60.0f);
				Update(1.0f / 60.0f);

				time -= sf::seconds(1.0f / 60.0f);
				counter += 1;
			}

			if(counter >= 10)
				time = sf::Time::Zero;

			_window->clear(sf::Color(100, 100, 100, 255));
			EntityManager::GetInstance()->Draw(_window);

			_window->display();
		}
	}

	void World::Update(float timeStep)
	{
		_window->setView(*_view);//?
	}
}
