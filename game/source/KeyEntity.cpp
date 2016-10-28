//
// Created by Matthias Bruns on 29/10/2016.
//

#include "KeyEntity.h"

namespace TT
{
    KeyEntity::KeyEntity(sf::Vector2f position) : Actor(position, "assets/textures/key.png") {
    }

    void KeyEntity::Update(float timeStep) {
        Actor::Update(timeStep);
    }

    void KeyEntity::Draw(sf::RenderWindow *window) {
        Actor::Draw(window);
    }
}