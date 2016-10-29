//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_ACTOR_H
#define TIMETRAVEL_ACTOR_H


#include "Entity.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

namespace TT {
    class Actor : public Entity {

    public:
        Actor(sf::Vector2f position, sf::String spritePath);
        ~Actor();

        virtual void Update(float timeStep);
        virtual void Draw(sf::RenderWindow *window);

        void OnCollisionStart(b2Contact* contact);
        void OnCollisionExit(b2Contact* contact);

    private:
        sf::Sprite *_object;
        b2Body *_body;
        b2Fixture *_boxFixture;

        sf::Vector2f _spawnPosition;
    };
}

#endif //TIMETRAVEL_ACTOR_H
