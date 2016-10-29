//
// Created by Nils Daumann on 17.08.16.
//

#include "World.h"
#include "PlayerEntity.h"
#include "NPC.h"
#include "Background.h"
#include "KeyEntity.h"
#include "Dialog.h"
#include "Clouds.h"
#include "ActorEmitter.h"
#include "GUIManager.h"
#include "LoadingScreen.h"
#include "Altar.h"
#include <iostream>

#if __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

//#define FULLSCREEN
#define SIMULATIONSTEP (1.0f/120.0f)

namespace TT
{
	bool World::KEYS[] = {false, false};
	World *World::_instance = nullptr;

	World *World::GetInstance()
	{
		if(!_instance)
		{
			_instance = new World();
		}

		return _instance;
	}

	World::World() : _physicsWorld(nullptr), _player(nullptr), _playerSpawnPosition(0.0f)
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
		_window->setVerticalSyncEnabled(true);

		float aspectRatio = static_cast<float>(_window->getSize().y)/static_cast<float>(_window->getSize().x);
		_view = new sf::View(sf::FloatRect(0.0f, -0.5*1920.0f*aspectRatio, 1920, 1920.0f*aspectRatio));
		_window->setView(*_view);
	}

	void World::LoadStartScreen() {
		_currentLevel = 0;
		Reset();

        new Background(1.0f, "assets/textures/startscreen/background.png"); //->1920

		if (!_bgm.openFromFile("assets/sounds/startscreen/bgm.ogg")) {
            cout << "WTF?" << endl;
		}

		Dialog::GetInstance()->SetText("Press ENTER to start");
    }

	bool World::SelectPuzzlePiece(int id)
	{
		if(_currentLevel == 2 && !World::KEYS[1])
		{
			if(_puzzleState == 0)
			{
				if (id == 0)
					_puzzleState = 1;
				else
					_puzzleState = 0;
			}
			else if(_puzzleState == 1)
			{
				if (id == 2)
					_puzzleState = 2;
				else
					_puzzleState = 0;
			}
			else if(_puzzleState == 2)
			{
				if (id == 1)
					_puzzleState = 3;
				else
					_puzzleState = 0;
			}

			if(_puzzleState == 3)
			{
				World::KEYS[1] = true;
				std::cout << "FUCK YEAH!" << std::endl;
			}

			if(_puzzleState == 0)
				std::cout << "ERROR!" << std::endl;

			return (_puzzleState > 0);
		}
	}

	void World::LoadLevel1()
	{
		_currentLevel = 1;

		Reset();
		new Background(1.0f, "assets/textures/level_1/6.png"); //->1920
		//new Clouds(20.0f, 0.8f, "assets/textures/level_1_early/2.png");
		new Background(0.7f, "assets/textures/level_1/5.png");
		new Background(0.5f, "assets/textures/level_1/4.png");
		new Background(0.0f, "assets/textures/level_1/3.png");

		if(!World::KEYS[0])
		{
			ActorEmitter *emitter = new ActorEmitter(sf::Vector2f(1555.0f, 150.0f));
			emitter->emitterOffset = sf::Vector2f(10.0f, 180.0f);
		}

		new NPC(sf::Vector2f(2350.0f, 278.5f));

		_player = new PlayerEntity(sf::Vector2f(_playerSpawnPosition, 285.0f));

		new Background(-0.3f, "assets/textures/level_1/2.png"); //->5759+(5759-1920)*0.5
		new Background(-0.7f, "assets/textures/level_1/1.png"); //->5759

		CreateStaticBoxCollider(sf::Vector2f(0.0f, 415.0f), sf::Vector2u(100000, 10));
		CreateStaticBoxCollider(sf::Vector2f(-5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		CreateStaticBoxCollider(sf::Vector2f(5759 + 5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		// LoadingScreen::GetInstance()->Fadeout();
	}

	void World::LoadLevel2()
	{
		_currentLevel = 2;

		Reset();

		new Background(1.0f, "assets/textures/level_2/6.png"); //->1920
		//new Background(0.8f, "assets/textures/level_1_early/2.png"); //->5759-(5759-1920)*0.8
		//new Clouds(20.0f, 0.8f, "assets/textures/level_1_early/2.png");
		new Background(0.7f, "assets/textures/level_2/5.png");
		new Background(0.5f, "assets/textures/level_2/4.png");
		new Background(0.0f, "assets/textures/level_2/3.png");

		_player = new PlayerEntity(sf::Vector2f(_playerSpawnPosition, 285.0f));

		new Altar(0, sf::Vector2f(2285, 278));
		new Altar(1, sf::Vector2f(2452, 278));
		new Altar(2, sf::Vector2f(2623, 278));

		new Background(-0.3f, "assets/textures/level_2/2.png"); //->5759+(5759-1920)*0.5
		new Background(-0.7f, "assets/textures/level_2/1.png"); //->5759

		CreateStaticBoxCollider(sf::Vector2f(0.0f, 415.0f), sf::Vector2u(100000, 10));
		CreateStaticBoxCollider(sf::Vector2f(-5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		CreateStaticBoxCollider(sf::Vector2f(3840 + 5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		// LoadingScreen::GetInstance()->Fadeout();
	}

	void World::LoadLevel3()
	{
		_currentLevel = 3;

		Reset();

		new Background(0.7f, "assets/textures/level_3/5.png");
		new Background(0.5f, "assets/textures/level_3/4.png");
		new Background(0.0f, "assets/textures/level_3/3.png");

		_player = new PlayerEntity(sf::Vector2f(_playerSpawnPosition, 285.0f));

		new Background(-0.3f, "assets/textures/level_3/2.png");
		new Background(-0.7f, "assets/textures/level_3/1.png");

		CreateStaticBoxCollider(sf::Vector2f(0.0f, 415.0f), sf::Vector2u(100000, 10));
		CreateStaticBoxCollider(sf::Vector2f(-5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		CreateStaticBoxCollider(sf::Vector2f(3840 + 5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		// LoadingScreen::GetInstance()->Fadeout();
	}

	void World::Reset()
	{
		_puzzleState = NULL;
        GUIManager::GetInstance()->RemoveAllWidgets();
		EntityManager::GetInstance()->RemoveAllEntities();
		_player = nullptr;

		if(_physicsWorld)
			delete _physicsWorld;

		b2Vec2 gravity(0.0f, 9.81f);
		_physicsWorld = new b2World(gravity);
        _physicsWorld->SetContactListener(&_contactListener);
	}

	void World::Loop()
	{
        LoadLevel3();

		sf::Clock clock;
		sf::Time deltaTime;
		sf::Time time = sf::Time::Zero;

		_bgm.setVolume(20.0f);
        _bgm.setLoop(true);
        _bgm.play();

		while(_window->isOpen())
		{
            HandleEvents();

            if(!_paused)
            {
                deltaTime = clock.restart();
                time += deltaTime;
                int counter = 0;
                while(time.asSeconds() >= SIMULATIONSTEP && counter < 10)
                {
	                _physicsWorld->Step(SIMULATIONSTEP, 8, 3);
	                EntityManager::GetInstance()->Update(SIMULATIONSTEP);
	                Update(SIMULATIONSTEP);

                    time -= sf::seconds(SIMULATIONSTEP);
                    counter += 1;
                }

                if (counter >= 10)
                {
	                time = sf::Time::Zero;
                }

	            float factor = time.asSeconds()/SIMULATIONSTEP;
	            EntityManager::GetInstance()->Interpolate(factor);
	            Interpolate(factor);

	           	Render();
            }
		}
	}

	void World::Render()
	{
		_window->setView(*_view);
		_window->clear(sf::Color::Black);
		EntityManager::GetInstance()->Draw(_window);

		_window->setView(sf::View(sf::FloatRect(0.0f, -0.5f * _window->getSize().y, _window->getSize().x, _window->getSize().y)));
		GUIManager::GetInstance()->Draw(_window);

		_window->display();
	}

	void World::Interpolate(float factor)
	{
		if(_view->getCenter().x < 0.0f)
		{
			_view->setCenter(0.0f, _view->getCenter().y);
		}

		if(_currentLevel == 1)
		{
			if(_view->getCenter().x > (5759.0f-_view->getSize().x))
			{
				_view->setCenter(5759.0f-_view->getSize().x, _view->getCenter().y);
			}
		}
		if(_currentLevel == 2)
		{
			if(_view->getCenter().x > (3840.0f-_view->getSize().x))
			{
				_view->setCenter(3840.0f-_view->getSize().x, _view->getCenter().y);
			}
		}
	}

	void World::Update(float timeStep)
	{
		GUIManager::GetInstance()->Update(timeStep);

		if(_player)
		{
			float windowWidth = _view->getSize().x;
			if(_currentLevel == 1)
			{
				if(_player->_position.x > 5650.0f-windowWidth*0.5f)
				{
					_playerSpawnPosition = -windowWidth*0.5f+200.0f;
					LoadingScreen::GetInstance()->Fadein();
					if (LoadingScreen::GetInstance()->Fadein())
					{
						LoadLevel2();
					}
				}
			}
			if(_currentLevel == 2)
			{
				if(_player->_position.x < -windowWidth*0.5f+100.0f)
				{
					_playerSpawnPosition = 5600-windowWidth*0.5;
					LoadingScreen::GetInstance()->Fadein();
					if (LoadingScreen::GetInstance()->Fadein())
					{
						LoadLevel1();
					}
				}
			}
		}
	}

    void World::HandleEvents()
    {
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
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						if(_currentLevel == 0){
							LoadLevel1();
						}
					}

					if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
					{
						cout << "PLAYER POSITION:" << _player->_position.x << " " << _player->_position.y << endl;
					}

					if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
					{
						if(_player) {
							_player->TriggerInteraction();
						}
					}

                    break;

                    // we don't process other types of events
                default:
                    break;
            }
        }
    }
}
