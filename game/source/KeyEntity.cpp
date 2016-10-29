//
// Created by Matthias Bruns on 29/10/2016.
//

#include "KeyEntity.h"
#include "PlayerEntity.h"
#include "World.h"

#include <iostream>

namespace TT
{
    KeyEntity::KeyEntity(sf::Vector2f position) : Actor(position, "assets/textures/key.png", b2_kinematicBody, true) {
    }

    void KeyEntity::Update(float timeStep) {
        Actor::Update(timeStep);
    }

    void KeyEntity::Draw(sf::RenderWindow *window) {
        Actor::Draw(window);
    }

    void KeyEntity::OnCollisionStart(b2Fixture *other) {
        Actor::OnCollisionStart(other);

        cout << "KeyEntity:OnCollisionStart" << endl;

        void *bodyUserData = other->GetUserData();
        if (bodyUserData) {
            PlayerEntity* player = static_cast<PlayerEntity *>( bodyUserData);
            if(player) {
                // Add to player
                World::KEYS[id] = true;

                // Remove from the universe
                EntityManager::GetInstance()->RemoveEntity(this);
            }
        }
    }
}