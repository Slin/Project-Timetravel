//
// Created by Matthias Bruns on 29/10/2016.
//

#include "NPC.h"
#include "PlayerEntity.h"
#include "Dialog.h"

namespace TT
{
    bool NPC::SOUNDS_LOADED = false;

    NPC::NPC(sf::Vector2f position) : Actor(position, "assets/textures/characters/npc_00.png", b2_kinematicBody, true, sf::Vector2f(5.0f, 5.0f)) {
        if(!SOUNDS_LOADED) {
            MUMBLES[0].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/mumble_00.ogg"));
            MUMBLES[1].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/mumble_01.ogg"));
            MUMBLES[2].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/mumble_02.ogg"));
            MUMBLES[3].setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/mumble_03.ogg"));
            SOUNDS_LOADED = true;
        }

        _animationFrames = _idleAnimationFrames;
        _animationSpeed = 1.0f;
    }

    void NPC::Update(float timeStep) {
        Actor::Update(timeStep);
        _playerIgnoreTimer -= timeStep;
        if(_playerIgnoreTimer < 0.0f) {
            _playerIgnoreTimer = 0.0f;
        }
    }

    void NPC::Draw(sf::RenderWindow *window) {
        Actor::Draw(window);
    }

    void NPC::OnCollisionStart(b2Fixture *other) {
        Actor::OnCollisionStart(other);


        if(_playerIgnoreTimer <= 0.0f) {
            void *bodyUserData = other->GetUserData();
            if (bodyUserData) {
                PlayerEntity *player = static_cast<PlayerEntity *>( bodyUserData);
                if (player) {
                    // Check for the password
                    if (World::KEYS[1]) {
                        // Allow to enter the next screne
                        PlayMumbleSound(3);
                        Dialog::GetInstance()->SetText("What... what did you do? You seem different.\nPlease enter whenever you are ready.");
                        Dialog::GetInstance()->SetResetTimer(3.2f);
                        canInteract = true;
                    } else {
                        // Write dialog

                        if (_talkCounter > 2) {
                            _talkCounter = 2;
                        }

                        switch (_talkCounter) {
                            case 0:
                                _playerIgnoreTimer = 3.2f;
                                Dialog::GetInstance()->SetText(
                                        "Hello stranger! You are not worthy to enter.");
                                break;
                            case 1:
                                _playerIgnoreTimer = 3.2f;
                                Dialog::GetInstance()->SetText(
                                        "I said that you are not allowed to pass this door.\nWhy are you bothering me? Leave me alone!");
                                break;
                            case 2:
                                _playerIgnoreTimer = 6.0f;
                                Dialog::GetInstance()->SetText(
                                        "Okay... Only those effected by the ancient powers are allowed to enter.\nNOT you.");
                                break;
                        }
                        Dialog::GetInstance()->SetResetTimer(_playerIgnoreTimer);
                        PlayMumbleSound(_talkCounter++);
                    }
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