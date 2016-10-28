//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_ACTOR_H
#define TIMETRAVEL_ACTOR_H


#include "Entity.h"

namespace TT {
    class Actor : public Entity{
    public:
        Actor(sf::Vector2f position, sf::String spritePath);
        ~Actor();

        virtual void Update(float timeStep);
        virtual void Draw(sf::RenderWindow *window);

    private:
        sf::Sprite *_object;
        b2Body *_body;
        b2Fixture *_boxFixture;

        sf::Vector2f _spawnPosition;
    };
}

#endif //TIMETRAVEL_ACTOR_H
