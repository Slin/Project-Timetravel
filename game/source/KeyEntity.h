//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_KEY_H
#define TIMETRAVEL_KEY_H

#include "Actor.h"

namespace TT {
    class KeyEntity : public Actor {
    public:
        KeyEntity(sf::Vector2f position);

        void Update(float timeStep);
        void Draw(sf::RenderWindow *window);

        virtual void OnCollisionStart(b2Fixture* other);
        virtual void OnCollisionExit(b2Fixture* other);

    private:
    };
}

#endif //TIMETRAVEL_KEY_H
