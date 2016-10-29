//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_ACTOREMITTER_H
#define TIMETRAVEL_ACTOREMITTER_H

#include "Actor.h"

namespace TT {
    class ActorEmitter: public Actor {

    public:
        int keyId = 0;
        bool emitOnce = true;
        sf::Vector2f emitterOffset;

        ActorEmitter(sf::Vector2f position);

        virtual void OnBlur(Entity* interactor);
        virtual void OnFocus(Entity* interactor);
        virtual void OnInteract(Entity* interactor);
    };
}


#endif //TIMETRAVEL_ACTOREMITTER_H
