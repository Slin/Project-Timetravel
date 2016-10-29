//
// Created by Nils Daumann on 17.08.16.
//

#include "World.h"
#include "PlayerEntity.h"
#include "Background.h"
#include "KeyEntity.h"
#include "Dialog.h"
#include "Clouds.h"

#include <iostream>

#if __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

//#define FULLSCREEN

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
		_window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Timetravel", sf::Style::Fullscreen);
#else
		_window = new sf::RenderWindow(sf::VideoMode(1920, 1200), "Timetravel");
#endif
		_window->setFramerateLimit(60);

		_view = new sf::View(sf::FloatRect(0.0f, -0.5*_window->getSize().y, _window->getSize().x, _window->getSize().y));
//		_view->zoom(1200.0f/_window->getSize().y);
		_window->setView(*_view);
	}

	void World::LoadLevelTest()
	{
		Reset();
		new Background(1.0f, "assets/textures/level_test/horizon.png");
		new Clouds(20.0f, 0.8f, "assets/textures/level_test/clouds.png");
		new Background(0.7f, "assets/textures/level_test/distant.png");
		new Background(0.5f, "assets/textures/level_test/back.png");
		new Background(0.0f, "assets/textures/level_test/walkable.png");

		new PlayerEntity(sf::Vector2f(0.0f, -100.0f));
		new KeyEntity(sf::Vector2f(100.0f, -100.0f));

		new Background(-0.5f, "assets/textures/level_test/front.png");

		CreateStaticBoxCollider(sf::Vector2f(0.0f, 415.0f), sf::Vector2u(100000, 10));
	}

	void World::LoadLevel1Early()
	{
		Reset();
		new Background(1.0f, "assets/textures/level_1_early/1.png"); //->1920
		new Background(0.8f, "assets/textures/level_1_early/2.png"); //->5759-(5759-1920)*0.8
		new Clouds(20.0f, 0.8f, "assets/textures/level_1_early/2.png");
		new Background(0.7f, "assets/textures/level_1_early/3.png");
		new Background(0.5f, "assets/textures/level_1_early/4.png"); //->5759+(5759-1920)*0.5
		new Background(0.0f, "assets/textures/level_1_early/5.png"); //->5759

		new PlayerEntity(sf::Vector2f(0.0f, -100.0f));
		//new KeyEntity(sf::Vector2f(100.0f, -100.0f));

		new Background(-0.3f, "assets/textures/level_1_early/6.png");
		new Background(-0.7f, "assets/textures/level_1_early/7.png");

		CreateStaticBoxCollider(sf::Vector2f(0.0f, 415.0f), sf::Vector2u(100000, 10));
		CreateStaticBoxCollider(sf::Vector2f(-5.0f - 0.5*_window->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		CreateStaticBoxCollider(sf::Vector2f(5759 + 5.0f - 0.5*_window->getSize().x, 0.0f), sf::Vector2u(10, 10000));
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
		Dialog::GetInstance();;

		LoadLevel1Early();

		sf::Clock clock;
		sf::Time deltaTime;
		sf::Time time = sf::Time::Zero;

		while(_window->isOpen())
		{
            HandleEvents();

            if(!_paused)
            {
                deltaTime = clock.getElapsedTime();
                time += deltaTime;
                clock.restart();
                int counter = 0;
                while (time.asSeconds() > 1.0f / 120.0f && counter < 20)
                {
                    Physics(1.0f / 120.0f);
					UpdateLogic(1.0f / 120.0f);

                    time -= sf::seconds(1.0f / 120.0f);
                    counter += 1;
                }

                if (counter >= 20)
                {
	                time = sf::Time::Zero;
                }

	           	Render();
            }
		}
	}

	void World::Physics(float fixedTime) {
		_physicsWorld->Step(fixedTime, 8, 3);
	}

	void World::UpdateLogic(float deltaTime) {
		EntityManager::GetInstance()->Update(deltaTime);
		Update(deltaTime);
	}

	void World::Render() {
		_window->setView(*_view);
		_window->clear(sf::Color::Black);
		EntityManager::GetInstance()->Draw(_window);

		_window->setView(sf::View(sf::FloatRect(0.0f, -0.5f * _window->getSize().y, _window->getSize().x, _window->getSize().y)));
		Dialog::GetInstance()->Draw(_window);

		_window->display();
	}

	void World::Update(float timeStep)
	{
		if(_view->getCenter().x < 0.0f)
		{
			_view->setCenter(0.0f, _view->getCenter().y);
		}

		if(_view->getCenter().x > (5759.0f-_window->getSize().x))
		{
			_view->setCenter(5759.0f-_window->getSize().x, _view->getCenter().y);
		}
	}

    void World::HandleEvents() {
        sf::Event event;

        // while there are pending events...
        while (_window->pollEvent(event))
        {
            // check the type of the event...
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    _window->close();
                    break;

                    // window blurred
                case sf::Event::LostFocus:
                    _paused = true;
                    break;

                    // window focussed
                case sf::Event::GainedFocus:
                    _paused = false;
                    break;

                    // key pressed
                case sf::Event::KeyPressed:
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        _window->close();
                    }

                    break;

                    // we don't process other types of events
                default:
                    break;
            }
        }
    }
}
