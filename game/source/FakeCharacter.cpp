//
// Created by Matthias Bruns on 30/10/2016.
//

#include "FakeCharacter.h"

namespace TT {

    FakeCharacter::FakeCharacter(sf::Vector2f position, string spritePath) : Actor(position, spritePath,
                                                                                   b2_kinematicBody, false,
                                                                                   sf::Vector2f(15.0f, 15.0f)) {
    }

    void FakeCharacter::Update(float timeStep) {
        Actor::Update(timeStep);
        if (fadeIn) {
            alpha += timeStep * 100.0f * fadeSpeed;
        }
        if (fadeOut) {
            alpha -= timeStep * 100.0f * fadeSpeed;
        }

        if (alpha < 0.0f) {
            alpha = 0.0f;
        }
        if (alpha > 255.0f) {
            alpha = 255.0f;
        }
    }

    void FakeCharacter::Draw(sf::RenderWindow *window) {
        _object->setColor(sf::Color(255, 255, 255, alpha));
        Actor::Draw(window);
    }

    void FakeCharacter::MoveTo(sf::Vector2f position) {

    }

    void FakeCharacter::StartFadeIn(bool reset) {
        fadeIn = true;
        fadeOut = false;
        if (reset || alpha >= 255.0f) {
            alpha = 0.0f;
        }
    }

    void FakeCharacter::StartFadeOut(bool reset) {
        fadeIn = false;
        fadeOut = true;
        if (reset || alpha <= 0.0f) {
            alpha = 255.0f;
        }
    }

}
