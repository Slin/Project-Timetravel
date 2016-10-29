//
// Created by Matthias Bruns on 29/10/2016.
//

#include "Actor.h"

namespace TT {
    void ContactListener::BeginContact(b2Contact *contact) {
        //check if fixture A was a Actor
        void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData) {
            static_cast<Actor *>( bodyUserData )->OnCollisionStart(contact->GetFixtureB());
        }

        //check if fixture B was a Actor
        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData)
            static_cast<Actor *>( bodyUserData )->OnCollisionStart(contact->GetFixtureA());

    }

    void ContactListener::EndContact(b2Contact *contact) {

        //check if fixture A was a Actor
        void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData)
            static_cast<Actor *>( bodyUserData )->OnCollisionExit(contact->GetFixtureB());

        //check if fixture B was a Actor
        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData)
            static_cast<Actor *>( bodyUserData )->OnCollisionExit(contact->GetFixtureA());

    }
}