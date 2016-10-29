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
        Actor(sf::Vector2f position, sf::String spritePath, b2BodyType bodyType = b2_dynamicBody, bool sensor = false, sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));
        ~Actor();

        virtual void Update(float timeStep);
        virtual void Draw(sf::RenderWindow *window);

        virtual void OnCollisionStart(b2Fixture* other);
        virtual void OnCollisionExit(b2Fixture* other);

        bool canInteract = false;

    private:
        sf::Sprite *_object;
        b2Body *_body;
        b2Fixture *_boxFixture;

        sf::Vector2f _spawnPosition;
    };
}

#endif //TIMETRAVEL_ACTOR_H
