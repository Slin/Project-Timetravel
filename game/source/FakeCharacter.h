//
// Created by Matthias Bruns on 30/10/2016.
//

#ifndef TIMETRAVEL_FAKECHARACTER_H
#define TIMETRAVEL_FAKECHARACTER_H

#include "Actor.h"

namespace TT {

    class FakeCharacter : public Actor {
        public:
            FakeCharacter(sf::Vector2f position, string spritePath);

            void Update(float timeStep) override ;
            void Draw(sf::RenderWindow *window) override;

            void MoveTo(sf::Vector2f position);
    };

}


#endif //TIMETRAVEL_FAKECHARACTER_H
