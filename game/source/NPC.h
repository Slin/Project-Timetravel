//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_NPC_H
#define TIMETRAVEL_NPC_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Actor.h"

namespace TT
{
	class NPC : public Actor {
	public:
        NPC(sf::Vector2f position);

		void Update(float timeStep) override ;
		void Draw(sf::RenderWindow *window) override;

        void OnCollisionStart(b2Fixture* other) override;
        void OnCollisionExit(b2Fixture* other) override;

        void OnBlur(Entity* interactor) override ;
        void OnFocus(Entity* interactor) override ;
        void OnInteract(Entity* interactor) override ;

    private:
		static bool SOUNDS_LOADED;
		static sf::Sound MUMBLES[];

		void PlayMumbleSound(unsigned int id);

        int _talkCounter = 0;
		int _idleAnimationFrames = 14;
	};
}

#endif //TIMETRAVEL_NPC_H
