//
// Created by Nils Daumann on 17.08.16.
//

#include "PlayerEntity.h"

#include <iostream>

namespace TT
{
	PlayerEntity::PlayerEntity(sf::Vector2f position) : _animationTimer(0.0f)
	{
		_object = nullptr;

		_object = World::CreateSprite("assets/textures/player.png", false);
		_object->setTextureRect(sf::IntRect(0, 0, 64, 64));
		_object->setOrigin(_object->getLocalBounds().width*0.5f, _object->getLocalBounds().height*0.5f);
		_object->move(position);
		_object->scale(5.0f, 5.0f);

		b2BodyDef bodyDef;
		b2PolygonShape dynamicBox;
		b2FixtureDef fixtureDef;

		bodyDef.type = b2_dynamicBody;
		bodyDef.linearDamping = 0.0f;
		bodyDef.position.Set(_object->getPosition().x*WORLD_TO_BOX2D, _object->getPosition().y*WORLD_TO_BOX2D);
		_body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&bodyDef);
		dynamicBox.SetAsBox(_object->getGlobalBounds().width*0.2f*WORLD_TO_BOX2D, (_object->getGlobalBounds().height*0.5f-30.0f)*WORLD_TO_BOX2D);
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 0.02f;
		fixtureDef.friction = 0.0f;
		fixtureDef.userData = (void*)this;
		_boxFixture = _body->CreateFixture(&fixtureDef);
		_body->SetFixedRotation(true);
		_body->SetBullet(true);

		// _sound.setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/jump.ogg"));
	}

	PlayerEntity::~PlayerEntity()
	{
		delete _object;
		World::GetInstance()->GetPhysicsWorld()->DestroyBody(_body);
	}

	bool PlayerEntity::IsGrounded()
	{
		bool grounded = false;
		bool blocked = false;
		b2Contact *contact = World::GetInstance()->GetPhysicsWorld()->GetContactList();
		while(contact)
		{
			if(contact->IsTouching() && (contact->GetFixtureA() == _boxFixture || contact->GetFixtureB() == _boxFixture))
			{
				contact->SetFriction(_boxFixture->GetFriction());
				b2WorldManifold manifold;
				contact->GetWorldManifold(&manifold);

				grounded = (grounded || ((contact->GetFixtureA() == _boxFixture)?(manifold.normal.y > 0.4f):(manifold.normal.y < -0.4f)));
				blocked = (blocked || ((contact->GetFixtureA() == _boxFixture)?(manifold.normal.y < -0.2f):(manifold.normal.y > 0.2f)));
			}

			contact = contact->GetNext();
		}
		return (grounded && !blocked);
	}

	void PlayerEntity::Update(float timeStep)
	{
		sf::Vector2f moveDirection;

		moveDirection.x = sf::Keyboard::isKeyPressed(sf::Keyboard::D)-sf::Keyboard::isKeyPressed(sf::Keyboard::A);

		if(fabsf(moveDirection.x) > 0.0f)
		{
			sf::Vector2f scale = _object->getScale();
			if(scale.x*moveDirection.x < 0.0f)
			{
				_object->setScale(-scale.x, scale.y);
			}
		}

		_body->ApplyLinearImpulse(b2Vec2((moveDirection.x*3.0f-_body->GetLinearVelocity().x)*_body->GetMass(), 0.0f), _body->GetWorldCenter(), true);


		if(_object && _body)
		{
			_object->setPosition(_body->GetPosition().x/WORLD_TO_BOX2D, _body->GetPosition().y/WORLD_TO_BOX2D);
			_object->setRotation(_body->GetAngle()*180.0f/3.14f);
		}

		const b2Vec2 &velocity = _body->GetLinearVelocity();
		// Animation stuff
		float frames = 8.0f;
		if(fabsf(velocity.x) > 0.5f)
		{
			// WALK
			frames = 8.0f;
			_animationTimer += timeStep * frames;
			if(_animationTimer >= frames)
				_animationTimer -= frames;

			_object->setTextureRect(sf::IntRect(((int)_animationTimer)*64, 64 * 4, 64, 64));
		} else {
			// IDLE
			frames = 14.0f;
			_animationTimer += timeStep * frames;
			if(_animationTimer >= frames)
				_animationTimer -= frames;

			_object->setTextureRect(sf::IntRect(((int)_animationTimer)*64, 0, 64, 64));
		}

		World::GetInstance()->GetView()->setCenter(_object->getPosition().x, 0.0f);
	}

	void PlayerEntity::Draw(sf::RenderWindow *window)
	{
		if(_object)
			window->draw(*_object);
	}
}