//
// Created by Nils Daumann on 29.10.16.
//

#include "Entity.h"

#ifndef TIMETRAVEL_ALTAR_H
#define TIMETRAVEL_ALTAR_H

namespace TT
{
	class Altar : public Entity
	{
	public:
		Altar();
		~Altar();

		void Update(float timestep);
		void Draw(sf::Window *_window);
	};
}

#endif //TIMETRAVEL_ALTAR_H
