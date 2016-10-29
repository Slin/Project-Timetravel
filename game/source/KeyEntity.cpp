//
// Created by Matthias Bruns on 29/10/2016.
//

#include "KeyEntity.h"
#include "PlayerEntity.h"
#include "World.h"

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

        void *bodyUserData = other->GetBody()->GetUserData();
        if (bodyUserData) {
            PlayerEntity* player = static_cast<PlayerEntity *>( bodyUserData);
            if(player) {
                // Add to player
                World::key_01 = true;

                // Remove from the universe
                EntityManager::GetInstance()->RemoveEntity(this);
            }
        }



    }
}