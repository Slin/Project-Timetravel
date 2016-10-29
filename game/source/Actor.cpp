//
// Created by Matthias Bruns on 29/10/2016.
//

#include "Actor.h"
#include <iostream>

namespace TT
{
    Actor::Actor(sf::Vector2f position, sf::String spritePath, b2BodyType bodyType, bool sensor, sf::Vector2f scale) {
        _object = nullptr;

        _object = World::CreateSprite(spritePath, false);
        _object->setTextureRect(sf::IntRect(0, 0, 64, 64));
        _object->setOrigin(_object->getLocalBounds().width * 0.5f, _object->getLocalBounds().height * 0.5f);
        _object->move(position);
        _object->scale(scale);

        b2BodyDef bodyDef;
        b2PolygonShape dynamicBox;
        b2FixtureDef fixtureDef;

        bodyDef.type = bodyType;
        //bodyDef.linearDamping = 10.0f;
        bodyDef.position.Set(_object->getPosition().x * WORLD_TO_BOX2D, _object->getPosition().y * WORLD_TO_BOX2D);
        bodyDef.userData = (void *) this;
        _body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&bodyDef);
        dynamicBox.SetAsBox(_object->getLocalBounds().width * 0.2f * WORLD_TO_BOX2D,
                            _object->getLocalBounds().height * 0.5f * WORLD_TO_BOX2D);
        fixtureDef.shape = &dynamicBox;

        if (bodyType == b2_dynamicBody) {
            fixtureDef.density = 1.0f;
            fixtureDef.friction = 10.0f;
        }

        fixtureDef.userData = (void*)this;
        fixtureDef.isSensor = sensor;

        _boxFixture = _body->CreateFixture(&fixtureDef);
        _body->SetFixedRotation(true);

        // _sound.setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/jump.ogg"));
    }

    Actor::~Actor()
    {
        cout << "Actor::~Actor" << endl;
        World::GetInstance()->GetPhysicsWorld()->DestroyBody(_body);
        delete _object;
    }

    void Actor::Update(float timeStep)
    {
        if(_object && _body)
        {
            _object->setPosition(_body->GetPosition().x/WORLD_TO_BOX2D, _body->GetPosition().y/WORLD_TO_BOX2D);
            _object->setRotation(_body->GetAngle()*180.0f/3.14f);
        }
    }

    void Actor::Draw(sf::RenderWindow *window)
    {
        if(_object)
            window->draw(*_object);
    }

    void Actor::OnCollisionStart(b2Fixture *other) {

    }

    void Actor::OnCollisionExit(b2Fixture *other) {

    }

    void Actor::OnBlur(Entity *interactor) {

    }

    void Actor::OnFocus(Entity *interactor) {

    }

    void Actor::OnInteract(Entity *interactor) {

    }
}