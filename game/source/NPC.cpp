//
// Created by Matthias Bruns on 29/10/2016.
//

#include "NPC.h"
#include "PlayerEntity.h"
#include "Dialog.h"

namespace TT
{
    NPC::NPC(sf::Vector2f position) : Actor(position, "assets/textures/npc_00.png", b2_kinematicBody, true, sf::Vector2f(5.0f, 5.0f)) {
    }

    void NPC::Update(float timeStep) {
        Actor::Update(timeStep);
    }

    void NPC::Draw(sf::RenderWindow *window) {
        Actor::Draw(window);
    }

    void NPC::OnCollisionStart(b2Fixture *other) {
        Actor::OnCollisionStart(other);

        void *bodyUserData = other->GetUserData();
        if (bodyUserData) {
            PlayerEntity* player = static_cast<PlayerEntity *>( bodyUserData);
            if(player) {
                // Check for the password
                if(World::PASSWORD_01){
                    // Allow to enter the next screne
                } else {
                    // Write dialog
                    Dialog::GetInstance()->SetText("Hello stranger! What is the password? You don't know it? Then you cannot enter...");
                }
            }
        }
    }

    void NPC::OnCollisionExit(b2Fixture *other) {
        Actor::OnCollisionExit(other);

        void *bodyUserData = other->GetUserData();
        if (bodyUserData) {
            PlayerEntity* player = static_cast<PlayerEntity *>( bodyUserData);
            if(player) {
                // Write dialog
                Dialog::GetInstance()->SetText("");
            }
        }
    }
}