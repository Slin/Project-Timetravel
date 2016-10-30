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
#include "Cutscene.h"
#include "Altar.h"
#include "Bookshelf.h"
#include "PulsatingLight.h"
#include "ParticleEmitter.h"
#include <iostream>

#if __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

//#define FULLSCREEN
#define SIMULATIONSTEP (1.0f/120.0f)

namespace TT
{
	bool World::KEYS[2] = {false, false};
	World *World::_instance = nullptr;

	World *World::GetInstance()
	{
		if(!_instance)
		{
			_instance = new World();
		}

		return _instance;
	}

	World::World() : _physicsWorld(nullptr), _player(nullptr), _playerSpawnPosition(0.0f), _wantsToLoadLevel(-1), _level1KeyLight(nullptr)
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

    void World::LoadLevel(int level)
    {
        _wantsToLoadLevel = level;
    }

	void World::LoadStartScreen()
	{
        KEYS[0] = false;
        KEYS[1] = false;

		_currentLevel = 0;
		Reset();

		_bgm.stop();
		_fx.stop();
		_fx.openFromFile("assets/sounds/rain.ogg");
		_fx.setLoop(true);
		_fx.setVolume(100.0f);

        new Background(1.0f, "assets/textures/startscreen/background.png"); //->1920

		Dialog::GetInstance()->SetText("Press ENTER to start");

		LoadingScreen::GetInstance()->Fadeout();

        _fx.play();

    }

	void World::LoadLevel1()
	{
		_currentLevel = 1;

		Reset();
		new Background(0.0f, "assets/textures/level_1/6.png"); //->1920
		new Clouds(0.0f, 0.8f, "assets/textures/level_1/clouds.png");
		new Background(0.7f, "assets/textures/level_1/5.png");
		new Background(0.5f, "assets/textures/level_1/4.png");
		new Background(0.0f, "assets/textures/level_1/3.png");

		new PulsatingLight("assets/textures/level_1/cavelight.png", sf::Vector2f(5254 - 0.5*_view->getSize().x, 140), 2.0f, 0.25f);

		if(!World::KEYS[0])
		{
			ActorEmitter *emitter = new ActorEmitter(sf::Vector2f(1440.0f, 278.0f));
			emitter->emitterOffset = sf::Vector2f(0.0f, 180.0f);

			_level1KeyLight = new PulsatingLight("assets/textures/level_1/keylight.png", sf::Vector2f(2413 - 0.5*_view->getSize().x, 184), 5.0f, 0.2f);
		}

		new NPC(sf::Vector2f(2350.0f, 278.5f));

		_player = new PlayerEntity(sf::Vector2f(_playerSpawnPosition, 285.0f));
		new Background(-0.3f, "assets/textures/level_1/2.png"); //->5759+(5759-1920)*0.5
		new Background(-0.7f, "assets/textures/level_1/1.png"); //->5759

		CreateStaticBoxCollider(sf::Vector2f(0.0f, 415.0f), sf::Vector2u(100000, 10));
		CreateStaticBoxCollider(sf::Vector2f(-5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		CreateStaticBoxCollider(sf::Vector2f(5759 + 5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		LoadingScreen::GetInstance()->Fadeout();
		_player->level = _currentLevel;

		_bgm.openFromFile("assets/sounds/level_1/bgm.ogg");
		_bgm.setLoop(true);
		_bgm.setVolume(10.0f);
		_bgm.play();

		_fx.openFromFile("assets/sounds/rain.ogg");
		_fx.setLoop(true);
		_fx.setVolume(100.0f);
		_fx.play();

	}

	void World::LoadLevel2()
	{
		_currentLevel = 2;
		Reset();
		_bgm.stop();
		_fx.stop();

		_bgm.openFromFile("assets/sounds/level_2/mood.ogg");
		_bgm.setLoop(true);
		_bgm.setVolume(100.0f);

		_fx.openFromFile("assets/sounds/level_2/drops.ogg");
		_fx.setLoop(true);
		_fx.setVolume(100.0f);

		new Background(1.0f, "assets/textures/level_2/6.png");
		new Background(0.7f, "assets/textures/level_2/5.png");
		new Background(0.5f, "assets/textures/level_2/4.png");

		new ParticleEmitter();
		new Background(0.0f, "assets/textures/level_2/3.png");

		new PulsatingLight("assets/textures/level_2/glowrunes.png", sf::Vector2f(1386 - 0.5*_view->getSize().x, 128), 4.0f, 0.25f);

		new Altar(0, sf::Vector2f(2285, 278));
		new Altar(2, sf::Vector2f(2452, 278));
		new Altar(1, sf::Vector2f(2623, 278));

		_player = new PlayerEntity(sf::Vector2f(_playerSpawnPosition, 285.0f));

		new Background(-0.3f, "assets/textures/level_2/2.png");
		new Background(-0.7f, "assets/textures/level_2/1.png");

		CreateStaticBoxCollider(sf::Vector2f(0.0f, 415.0f), sf::Vector2u(100000, 10));
		CreateStaticBoxCollider(sf::Vector2f(-5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		CreateStaticBoxCollider(sf::Vector2f(3840 + 5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		LoadingScreen::GetInstance()->Fadeout();
		_player->level = _currentLevel;

		_fx.play();
		_bgm.play();
	}

	void World::LoadLevel3()
	{
		float windowWidth = _view->getSize().x;
		_playerSpawnPosition = -windowWidth*0.5f+200.0f;
		_currentLevel = 3;

		Reset();

		new Background(0.7f, "assets/textures/level_3/5.png");
		new Background(0.05f, "assets/textures/level_3/4.png");
		new Background(0.0f, "assets/textures/level_3/3.png");

		new Bookshelf(0, sf::Vector2f(-577, 278));
		new Bookshelf(1, sf::Vector2f(-114, 278));
		new Bookshelf(2, sf::Vector2f(198, 278));
		new Bookshelf(3, sf::Vector2f(544, 278));
		new Bookshelf(4, sf::Vector2f(856, 278));
		new Bookshelf(5, sf::Vector2f(639, 278));

		_player = new PlayerEntity(sf::Vector2f(_playerSpawnPosition, 285.0f));

		new Background(-0.3f, "assets/textures/level_3/2.png");
		new Background(-0.7f, "assets/textures/level_3/1.png");

		CreateStaticBoxCollider(sf::Vector2f(0.0f, 415.0f), sf::Vector2u(100000, 10));
		CreateStaticBoxCollider(sf::Vector2f(-5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		CreateStaticBoxCollider(sf::Vector2f(3840 + 5.0f - 0.5*_view->getSize().x, 0.0f), sf::Vector2u(10, 10000));
		LoadingScreen::GetInstance()->Fadeout();
		_player->level = _currentLevel;

		_bgm.openFromFile("assets/sounds/level_3/level3music.ogg");
		_bgm.setVolume(100.0f);
		_bgm.setLoop(true);
		_bgm.play();
		_fx.stop();

	}

	void World::Reset()
	{
		_puzzleState = 0;
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
		if(_currentLevel == 3)
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
		float windowWidth = _view->getSize().x;

		if(_wantsToLoadLevel > -1)
		{
			_playerSpawnPosition = -windowWidth*0.5f+200.0f;
			if(LoadingScreen::GetInstance()->Fadein())
			{
				if(_wantsToLoadLevel == 0)
					LoadStartScreen();
				if(_wantsToLoadLevel == 1)
					LoadLevel1();
				if(_wantsToLoadLevel == 2)
					LoadLevel2();
				if(_wantsToLoadLevel == 3)
					LoadLevel3();

				_wantsToLoadLevel = -1;
			}
		}

		if(_player)
		{
			if(_currentLevel == 1)
			{
				if(World::KEYS[0] && _level1KeyLight)
				{
					EntityManager::GetInstance()->RemoveEntity(_level1KeyLight);
					_level1KeyLight = nullptr;
				}

				if(_player->_position.x > 5650.0f-windowWidth*0.5f)
				{
					if(World::KEYS[0])
					{
						_playerSpawnPosition = -windowWidth*0.5f+200.0f;
						if(LoadingScreen::GetInstance()->Fadein())
						{
							LoadLevel2();
						}
					}
					else
					{
						Dialog::GetInstance()->SetText("The gate is locked.");
						Dialog::GetInstance()->SetResetTimer(3.0f);
					}
				}
			}
			if(_currentLevel == 2)
			{
				if(_player->_position.x < -windowWidth*0.5f+100.0f)
				{
					_playerSpawnPosition = 5600-windowWidth*0.5;
					if (LoadingScreen::GetInstance()->Fadein())
					{
						LoadLevel1();
					}
				}
			}
			if(_currentLevel == 3)
			{
				if(_player->_position.x < -windowWidth*0.5f+100.0f)
				{
					_playerSpawnPosition = 2460;
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

	            case sf::Event::Resized:
	            {
		            float aspectRatio = static_cast<float>(_window->getSize().y)/static_cast<float>(_window->getSize().x);
		            _view = new sf::View(sf::FloatRect(0.0f, -0.5*1920.0f*aspectRatio, 1920, 1920.0f*aspectRatio));
		            _window->setView(*_view);
		            break;
	            }

                    // key pressed
                case sf::Event::KeyPressed:
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        _window->close();
                    }
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						if(_currentLevel == 0)
						{
                            Cutscene::GetInstance()->StartCutscene(0);
						}
					}

					if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
					{
						cout << "PLAYER POSITION:" << _player->_position.x << " " << _player->_position.y << endl;
					}

					if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
                        // Cutscene::GetInstance()->SkipStep();

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
