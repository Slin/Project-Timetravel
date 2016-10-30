//
// Created by Nils Daumann on 17.08.16.
//

#include "PlayerEntity.h"
#include "Actor.h"

#include <iostream>
#include "Math.h"

namespace TT {
    PlayerEntity::PlayerEntity(sf::Vector2f position) : _animationTimer(0.0f) {
        _object = nullptr;
        _interactionTarget = nullptr;

        level = 1;
        _object = World::CreateSprite("assets/textures/characters/player.png", false);
        _object->setTextureRect(sf::IntRect(0, 0, 64, 64));
        _object->setOrigin(_object->getLocalBounds().width * 0.5f, _object->getLocalBounds().height * 0.5f);
        _object->move(position);
        _object->scale(5.0f, 5.0f);

        b2BodyDef bodyDef;
        b2PolygonShape dynamicBox;
        b2FixtureDef fixtureDef;

        bodyDef.type = b2_dynamicBody;
        bodyDef.linearDamping = 0.0f;
        bodyDef.position.Set(_object->getPosition().x * WORLD_TO_BOX2D, _object->getPosition().y * WORLD_TO_BOX2D);
        _body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&bodyDef);
        dynamicBox.SetAsBox(_object->getGlobalBounds().width * 0.2f * WORLD_TO_BOX2D,
                            (_object->getGlobalBounds().height * 0.5f - 30.0f) * WORLD_TO_BOX2D);
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 0.02f;
        fixtureDef.friction = 0.0f;
        fixtureDef.userData = (void *) this;
        _boxFixture = _body->CreateFixture(&fixtureDef);
        _body->SetFixedRotation(true);
        _body->SetBullet(true);


        // _sound.setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/jump.ogg"));
        _pickupSound.setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/pickup.ogg"));
        _walkingSoundForest.setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/walking.ogg"));
        _walkingSoundCave[0].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/cavefootstep1.ogg"));
        _walkingSoundCave[1].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/cavefootstep2.ogg"));
        _walkingSoundCave[2].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/cavefootstep3.ogg"));
        _walkingSoundCave[3].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/cavefootstep4.ogg"));
        _walkingSoundCave[4].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/cavefootstep5.ogg"));
        _walkingSoundCave[5].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/cavefootstep6.ogg"));
        _walkingSoundCave[6].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/cavefootstep7.ogg"));
		_walkingSoundCave[0].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/cavefootstep1.ogg"));
		_walkingSoundLibrary[0].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/libraryfootstep1.ogg"));
		_walkingSoundLibrary[1].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/libraryfootstep2.ogg"));
		_walkingSoundLibrary[2].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/libraryfootstep3.ogg"));
		_walkingSoundLibrary[3].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/walking/libraryfootstep4.ogg"));
        sound_counter = 0;
    }

    PlayerEntity::~PlayerEntity() {
        delete _object;
        World::GetInstance()->GetPhysicsWorld()->DestroyBody(_body);
    }

    bool PlayerEntity::IsGrounded() {
        bool grounded = false;
        bool blocked = false;
        b2Contact *contact = World::GetInstance()->GetPhysicsWorld()->GetContactList();
        while (contact) {
            if (contact->IsTouching() &&
                (contact->GetFixtureA() == _boxFixture || contact->GetFixtureB() == _boxFixture)) {
                contact->SetFriction(_boxFixture->GetFriction());
                b2WorldManifold manifold;
                contact->GetWorldManifold(&manifold);

                grounded = (grounded ||
                            ((contact->GetFixtureA() == _boxFixture) ? (manifold.normal.y > 0.4f) : (manifold.normal.y <
                                                                                                     -0.4f)));
                blocked = (blocked ||
                           ((contact->GetFixtureA() == _boxFixture) ? (manifold.normal.y < -0.2f) : (manifold.normal.y >
                                                                                                     0.2f)));
            }

            contact = contact->GetNext();
        }
        return (grounded && !blocked);
    }

    void PlayerEntity::Update(float timeStep) {
        sf::Vector2f moveDirection;
        if(!_disabled) {
            moveDirection.x = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        } else {
            moveDirection.x = 0.0f;
        }

        if (fabsf(moveDirection.x) > 0.0f) {
            sf::Vector2f scale = _object->getScale();
            if (scale.x * moveDirection.x < 0.0f) {
                _object->setScale(-scale.x, scale.y);
            }
        }

        _body->ApplyLinearImpulse(
                b2Vec2((moveDirection.x * 5.0f - _body->GetLinearVelocity().x) * _body->GetMass(), 0.0f),
                _body->GetWorldCenter(), true);

        if (_object && _body) {
            _previousPosition = _position;
            _position = sf::Vector2f(_body->GetPosition().x / WORLD_TO_BOX2D, _body->GetPosition().y / WORLD_TO_BOX2D);
        }

        const b2Vec2 &velocity = _body->GetLinearVelocity();
        // Animation stuff
        float frames = 8.0f;
        if (fabsf(velocity.x) > 0.5f) {
            

            // WALK
            frames = 8.0f;
            _animationTimer += timeStep * 8.5f;
            if (_animationTimer >= frames)
                _animationTimer -= frames;
			PlayWalkingSounds();
            _object->setTextureRect(sf::IntRect(((int) _animationTimer) * 64, 64 * 4, 64, 64));
        } else {
            // IDLE
            StopPlayingWalking();
            frames = 14.0f;
            _animationTimer += timeStep * 5.0f;
            if (_animationTimer >= frames)
                _animationTimer -= frames;

            _object->setTextureRect(sf::IntRect(((int) _animationTimer) * 64, 0, 64, 64));
        }

        FindInteractionObjects();
    }

    void PlayerEntity::Interpolate(float factor) {
        Entity::Interpolate(factor);
        World::GetInstance()->GetView()->setCenter(_position.x, 0.0f);
    }

    void PlayerEntity::Draw(sf::RenderWindow *window) {
        if (_object && !_hidden) {
            _object->setPosition(_position);
            _object->setRotation(_body->GetAngle() * 180.0f / 3.14f);

            window->draw(*_object);
        }
    }

	sf::Vector2f PlayerEntity::GetVelocity()
	{
		return sf::Vector2f(_body->GetLinearVelocity().x, _body->GetLinearVelocity().y);
	}

    void PlayerEntity::FindInteractionObjects() {
        float radius = 50.0f * WORLD_TO_BOX2D;

        // Check distance to interactionTarget
        if (_interactionTarget) {
            float distance = Math::distance(_interactionTarget->_position, _position) * WORLD_TO_BOX2D;
            if (!_interactionTarget->canInteract || distance > radius) {
                _interactionTarget->OnBlur(this);
                _interactionTarget = nullptr;
            }
        }

        b2AABB aabb;
        aabb.lowerBound = _body->GetWorldCenter() - b2Vec2(radius, radius);
        aabb.upperBound = _body->GetWorldCenter() + b2Vec2(radius, radius);

        World::GetInstance()->GetPhysicsWorld()->QueryAABB(this, aabb);
    }

    bool PlayerEntity::ReportFixture(b2Fixture *fixture) {
        void *bodyUserData = fixture->GetUserData();
        if (bodyUserData && bodyUserData != this) {
            Actor *actor = static_cast<Actor *>(bodyUserData);
            if (actor->canInteract) {
                if (actor != _interactionTarget) {
                    if (_interactionTarget)
                        _interactionTarget->OnBlur(_interactionTarget);
                    _interactionTarget = actor;
                    _interactionTarget->OnFocus(this);
                }

                return false;
            }
        }
        return true;
    }

    void PlayerEntity::TriggerInteraction() {
        if (_interactionTarget) {
            _interactionTarget->OnInteract(this);
        }
    }

    void PlayerEntity::PlayPickupSound() {
        _pickupSound.play();
    };

    void PlayerEntity::PlayWalkingSounds() {
        if (level == 1) {
            if (_animationTimer > 0.95 && _animationTimer < 1.02 &&
                (_walkingSoundForest.getStatus() == sf::Sound::Status::Stopped))
                _walkingSoundForest.play();
            if (_animationTimer > 3.95 && _animationTimer < 4.02 &&
                (_walkingSoundForest.getStatus() == sf::Sound::Status::Stopped))
                _walkingSoundForest.play();
            if (_animationTimer > 6.95 && _animationTimer < 7.02 &&
                (_walkingSoundForest.getStatus() == sf::Sound::Status::Stopped))
                _walkingSoundForest.play();
        }

        if (level == 2) {
			
            if ((_animationTimer > 1.03 && _animationTimer < 1.13) ||
                (_animationTimer > 5.00 && _animationTimer < 5.13) ) 
			{
                _walkingSoundCave[sound_counter % 7].play();
                sound_counter++;
            }
        }

		if (level == 3)
		{
			if ((_animationTimer > 1.03 && _animationTimer < 1.13) ||
				(_animationTimer > 5.00 && _animationTimer < 5.13))
			{
				_walkingSoundLibrary[sound_counter % 4].play();
				sound_counter++;
			}

		}
    }

    void PlayerEntity::StopPlayingWalking() {
        _walkingSoundForest.stop();
    }
}