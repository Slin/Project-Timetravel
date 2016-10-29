//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_ACTOR_H
#define TIMETRAVEL_ACTOR_H


#include "Entity.h"
#include "Box2D/Dynamics/b2Fixture.h"

namespace TT {
    class Actor : public Entity {

    public:
        bool canInteract = false;
        bool hidden = false;

        Actor(sf::Vector2f position, sf::String spritePath, b2BodyType bodyType = b2_dynamicBody, bool sensor = false, sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f), sf::Vector2f size = sf::Vector2f(64.0f, 64.0f));
        ~Actor();

        virtual void Update(float timeStep);
        virtual void Draw(sf::RenderWindow *window);
        virtual void Animate(float timeStep);

        virtual void OnCollisionStart(b2Fixture* other);
        virtual void OnCollisionExit(b2Fixture* other);

        virtual void OnBlur(Entity* interactor);
        virtual void OnFocus(Entity* interactor);
        virtual void OnInteract(Entity* interactor);

        b2Body* GetBody(){
            return _body;
        }

    protected:
        int _spriteIndex = 0;
        sf::Vector2f _size;
        int _animationFrames = 0;
        float _animationTimer = 0.0f;
        float _animationSpeed = 1.0f;
        sf::Sprite *_object;

    private:
        b2Body *_body;
        b2Fixture *_boxFixture;
        sf::Vector2f _spawnPosition;
    };
}

#endif //TIMETRAVEL_ACTOR_H
