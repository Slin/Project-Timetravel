//
// Created by Matthias Bruns on 29/10/2016.
//

#include "NPC.h"
#include "PlayerEntity.h"
#include "Dialog.h"

namespace TT
{
    bool NPC::SOUNDS_LOADED = false;
    sf::Sound NPC::MUMBLES[4];

    NPC::NPC(sf::Vector2f position) : Actor(position, "assets/textures/characters/npc_00.png", b2_kinematicBody, true, sf::Vector2f(5.0f, 5.0f)) {
        if(!SOUNDS_LOADED) {
            MUMBLES[0].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/mumble_00.ogg"));
            MUMBLES[0].setVolume(90.0f);
            MUMBLES[1].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/mumble_01.ogg"));
            MUMBLES[1].setVolume(90.0f);
            MUMBLES[2].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/mumble_02.ogg"));
            MUMBLES[2].setVolume(90.0f);
            MUMBLES[3].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/mumble_03.ogg"));
            MUMBLES[3].setVolume(90.0f);
            SOUNDS_LOADED = true;
        }

        _animationFrames = _idleAnimationFrames;
        _animationSpeed = 1.0f;
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
                if(World::KEYS[1]){
                    // Allow to enter the next screne
                    PlayMumbleSound(4);
                    Dialog::GetInstance()->SetText("Correct! You've found the password. You can now enter the dungeon.");
                    Dialog::GetInstance()->SetResetTimer(3.2f);
                    PlayMumbleSound(4);
                    canInteract = true;
                } else {
                    // Write dialog

                    if(_talkCounter > 2) {
                        _talkCounter = 2;
                    }

                    switch (_talkCounter) {
                        case 0:
                            Dialog::GetInstance()->SetText("Hello stranger! What is the password? You don't know it? Then you cannot enter...");
                            Dialog::GetInstance()->SetResetTimer(3.2f);
                            break;
                        case 1:
                            Dialog::GetInstance()->SetText("You have still no key. Why are you bothering me? Leave me alone!");
                            Dialog::GetInstance()->SetResetTimer(3.2f);
                            break;
                        case 2:
                            Dialog::GetInstance()->SetText("You need to go to the cave in the East from here. Do that stupid riddle and come back with the password.");
                            Dialog::GetInstance()->SetResetTimer(6.0f);
                            break;
                    }
                    PlayMumbleSound(_talkCounter++);
                }
            }
        }
    }

    void NPC::OnCollisionExit(b2Fixture *other) {
        Actor::OnCollisionExit(other);

        void *bodyUserData = other->GetUserData();
        if (bodyUserData) {
            PlayerEntity *player = static_cast<PlayerEntity *>( bodyUserData);
            if (player) {
                // Write dialog
                // Dialog::GetInstance()->SetText("");
            }
        }
    }

    void NPC::PlayMumbleSound(unsigned int id) {
        if (MUMBLES[id].getStatus() != sf::SoundSource::Playing) {
            MUMBLES[id].play();
        }
    }

    void NPC::OnBlur(Entity *interactor) {
        Actor::OnBlur(interactor);
    }

    void NPC::OnFocus(Entity *interactor) {
        Actor::OnFocus(interactor);
    }

    void NPC::OnInteract(Entity *interactor) {
        Actor::OnInteract(interactor);
        World::GetInstance()->GetInstance()->LoadLevel(3);
    }
}