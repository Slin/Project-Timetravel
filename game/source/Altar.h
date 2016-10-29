//
// Created by Nils Daumann on 29.10.16.
//

#include "Actor.h"

#ifndef TIMETRAVEL_ALTAR_H
#define TIMETRAVEL_ALTAR_H

namespace TT
{
	class Altar : public Actor
	{
	public:
		Altar(sf::Vector2f position);
		~Altar();

		void Update(float timestep);
		void Draw(sf::RenderWindow *_window);

		void OnBlur(Entity *interactor);
		void OnFocus(Entity *interactor);
		void OnInteract(Entity *interactor);
	};
}

#endif //TIMETRAVEL_ALTAR_H
