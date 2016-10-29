//
// Created by Matthias Bruns on 29/10/2016.
//

#include "ActorEmitter.h"
namespace TT {
    ActorEmitter::ActorEmitter(sf::Vector2f position) : Actor(position, "assets/textures/none.png", b2_kinematicBody, true) {
        canInteract = true;
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
    }
};
