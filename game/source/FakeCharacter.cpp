//
// Created by Matthias Bruns on 30/10/2016.
//

#include "FakeCharacter.h"

namespace TT {

    FakeCharacter::FakeCharacter(sf::Vector2f position, string spritePath) : Actor(position, spritePath, b2_kinematicBody, false, sf::Vector2f(15.0f, 15.0f)) {

    }

    void FakeCharacter::Update(float timeStep) {
        Actor::Update(timeStep);
    }

    void FakeCharacter::Draw(sf::RenderWindow *window) {
        Actor::Draw(window);
    }

    void FakeCharacter::MoveTo(sf::Vector2f position) {

    }

}
