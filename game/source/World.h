//
// Created by Nils Daumann on 17.08.16.
//

#ifndef TIMETRAVEL_WORLD_H
#define TIMETRAVEL_WORLD_H


#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>

#include "EntityManager.h"
#include "Entity.h"
#include "TexturePool.h"
#include "SoundPool.h"
#include "ContactListener.h"
#include <list>

#define WORLD_TO_BOX2D 0.01f

namespace TT
{
	class PlayerEntity;
	class World
	{
	public:
        static bool KEY_01;
		static bool PASSWORD_01;

		void Loop();
		void Update(float timeStep);
		void Interpolate(float factor);

		sf::RenderWindow *GetWindow() const
		{
			return _window;
		}

        const bool IsPaused(){
            return _paused;
        }

		const std::string &GetBundlePath() const
		{
			return _bundlePath;
		}

		b2World *GetPhysicsWorld() const
		{
			return _physicsWorld;
		}

		sf::View *GetView() const
		{
			return _view;
		}

		static World *GetInstance();

		static sf::Sprite *CreateSprite(const std::string &file, bool smooth = true)
		{
			sf::Sprite *object = new sf::Sprite();
			sf::Texture *pTexture = TexturePool::GetInstance()->GetTexture(file);
			pTexture->setSmooth(smooth);
			object->setTexture(*pTexture);
			
			object->setOrigin(object->getLocalBounds().width*0.5f, object->getLocalBounds().height*0.5f);

			return object;
		}

		static b2Body *CreateStaticBoxCollider(sf::Vector2f position, sf::Vector2u size, float rotation = 0.0f)
		{
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(position.x*WORLD_TO_BOX2D, position.y*WORLD_TO_BOX2D);
			groundBodyDef.angle = rotation/180.0f*3.14f;
			b2Body *body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&groundBodyDef);

			b2PolygonShape box;
			box.SetAsBox(size.x*WORLD_TO_BOX2D*0.5f, size.y*WORLD_TO_BOX2D*0.5f);
			body->CreateFixture(&box, 0.0f);

			return body;
		}

	private:
		World();

		void Reset();
		void LoadLevelTest();
		void LoadLevel1Early();
		void LoadLevel2Early();

		static World *_instance;
		ContactListener _contactListener;
		sf::RenderWindow *_window;
		sf::View *_view;
		float _scaleFactor;
		std::string _bundlePath;
        bool _paused = false;
		PlayerEntity *_player;

		b2World *_physicsWorld;
        std::list<b2Body*> _deadBodies;

		int _currentLevel;
		float _playerSpawnPosition;

        void HandleEvents();
        void Render();
	};
}


#endif //TIMETRAVEL_WORLD_H
