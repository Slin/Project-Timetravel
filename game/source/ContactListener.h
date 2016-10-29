//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_CONTACTLISTENER_H
#define TIMETRAVEL_CONTACTLISTENER_H

#include "Box2D/Dynamics/b2WorldCallbacks.h"

namespace TT {
    class Actor;
    class ContactListener : public b2ContactListener {
        virtual void BeginContact(b2Contact *contact);
        virtual void EndContact(b2Contact *contact);
    };
}
#endif //TIMETRAVEL_CONTACTLISTENER_H
