//
// Created by Matthias Bruns on 29/10/2016.
//

#include "ActorEmitter.h"
#include "KeyEntity.h"

namespace TT {
    ActorEmitter::ActorEmitter(sf::Vector2f position) : Actor(position, "assets/textures/none.png", b2_kinematicBody, true) {
        canInteract = true;
        hidden = true;
        emitterOffset = sf::Vector2f(0.0f, 0.0f);
    }

    void ActorEmitter::OnBlur(Entity *interactor) {
        Actor::OnBlur(interactor);
        _spriteIndex = 0;
    }

    void ActorEmitter::OnFocus(Entity *interactor) {
        Actor::OnFocus(interactor);
        _spriteIndex = 1;
    }

    void ActorEmitter::OnInteract(Entity *interactor) {
        Actor::OnInteract(interactor);
        if(keyId != -1) {
            KeyEntity *entity = new KeyEntity(_position + sf::Vector2f(200.0f, 175.0f));
            entity->id = keyId;
        }

        if(emitOnce) {
            // Remove from the universe
            canInteract = false;
        }
    }
};
