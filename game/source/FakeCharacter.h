//
// Created by Matthias Bruns on 30/10/2016.
//

#ifndef TIMETRAVEL_FAKECHARACTER_H
#define TIMETRAVEL_FAKECHARACTER_H

#include "Actor.h"

namespace TT {

    class FakeCharacter : public Actor {
        public:
            float maxAlpha = 255.0f;
            float minAlpha = 0.0f;

            FakeCharacter(sf::Vector2f position, string spritePath);

            void Update(float timeStep) override ;
            void Draw(sf::RenderWindow *window) override;

            void MoveTo(sf::Vector2f position);

            void StartFadeIn(bool reset);
            void StartFadeOut(bool reset);

    private:
        bool fadeIn = false;
        bool fadeOut = false;
        float alpha = 0.0f;
        float fadeSpeed = 1.0f;
    };

}


#endif //TIMETRAVEL_FAKECHARACTER_H
