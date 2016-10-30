//
// Created by Nils Daumann on 30.10.16.
//

#ifndef TIMETRAVEL_PORTAL_H
#define TIMETRAVEL_PORTAL_H

#include "Entity.h"

namespace TT
{
	class Portal : public Entity
	{
	public:
		Portal();
		~Portal();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

	private:
		sf::Sprite *_object;
		sf::Shader _shader;
	};
}

#endif //TIMETRAVEL_PORTAL_H
