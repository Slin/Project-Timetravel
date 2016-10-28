//
// Created by Nils Daumann on 17.08.16.
//

#include "PlayerEntity.h"

#include <iostream>

namespace TT
{
	PlayerEntity::PlayerEntity(int id, sf::Vector2f position) : _jumpTimer(100), _spawnPosition(position), _animationTimer(0.0f)
	{
		_object = nullptr;

		_object = World::CreateSprite("assets/textures/player.png");
		_object->setTextureRect(sf::IntRect(0, 0, 64, 64));
		_object->setOrigin(_object->getLocalBounds().width*0.5f, _object->getLocalBounds().height*0.5f);
		_object->move(position);

		// _object->setColor(((id==0)?sf::Color::Green:sf::Color::Blue));

		b2BodyDef bodyDef;
		b2PolygonShape dynamicBox;
		b2FixtureDef fixtureDef;

		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(_object->getPosition().x*WORLD_TO_BOX2D, _object->getPosition().y*WORLD_TO_BOX2D);
		_body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&bodyDef);
		dynamicBox.SetAsBox(_object->getLocalBounds().width*0.2f*WORLD_TO_BOX2D, _object->getLocalBounds().height*0.5f*WORLD_TO_BOX2D);
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 10.0f;
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
		moveDirection.y = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		moveDirection.x *= 0.07f;

		if(fabsf(moveDirection.x) > 0.0f)
		{
			_boxFixture->SetFriction(0.0f);

			sf::Vector2f scale = _object->getScale();
			if(scale.x*moveDirection.x < 0.0f)
			{
				_object->setScale(-scale.x, scale.y);
			}
		}
		else
		{
			_boxFixture->SetFriction(5.0f);
		}

		bool isGrounded = IsGrounded();
		if(moveDirection.y > 0.0f)
		{
			if(_jumpTimer > 1 && isGrounded)
			{
				_body->ApplyLinearImpulse(b2Vec2(0.0f, -1.0f), b2Vec2(_body->GetPosition().x, _body->GetPosition().y), true);
				_sound.setPitch(0.75f+(rand()/(float)INT_MAX)*0.5f);
				_sound.play();
			}
			_jumpTimer = 0;
		}
		else
		{
			_jumpTimer += 1;
		}

		if((moveDirection.x < 0.0f && _body->GetLinearVelocity().x > -2.0f) || (moveDirection.x > 0.0f && _body->GetLinearVelocity().x < 2.0f))
		{
			_body->ApplyLinearImpulse(b2Vec2(moveDirection.x*(isGrounded?1.0f:0.5f), 0.0f), b2Vec2(_body->GetPosition().x, _body->GetPosition().y), true);
		}

		if(_object && _body)
		{
			_object->setPosition(_body->GetPosition().x/WORLD_TO_BOX2D, _body->GetPosition().y/WORLD_TO_BOX2D);
			_object->setRotation(_body->GetAngle()*180.0f/3.14f);
		}

		const b2Vec2 &velocity = _body->GetLinearVelocity();
		// Animation stuff
		float frames = 8.0f;
		if(fabsf(velocity.x) > 0.0f)
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
	}

	void PlayerEntity::Draw(sf::RenderWindow *window)
	{
		if(_object)
			window->draw(*_object);
	}
}