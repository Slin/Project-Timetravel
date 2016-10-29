//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_KEY_H
#define TIMETRAVEL_KEY_H

#include "Actor.h"
#include "Box2D/Dynamics/b2Fixture.h"

namespace TT {
    class KeyEntity : public Actor {
    public:
        int id = 0;

        KeyEntity(sf::Vector2f position);
        ~KeyEntity();

        void Update(float timeStep) override;
        void Draw(sf::RenderWindow *window) override;

        void OnCollisionStart(b2Fixture* other) override;

    private:

        sf::Sound _sound;
    };
}

#endif //TIMETRAVEL_KEY_H
