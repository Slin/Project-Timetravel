//
// Created by Nils Daumann on 30.10.16.
//

#ifndef TIMETRAVEL_PORTAL_H
#define TIMETRAVEL_PORTAL_H

#include "Actor.h"

namespace TT
{
	class Portal : public Actor
	{
	public:
		Portal(sf::Vector2f position);
		~Portal();

		void Update(float timeStep) override;

		void OnInteract(Entity* interactor) override;

	private:
		sf::Sprite *_object;
		sf::Shader _shader;
	};
}

#endif //TIMETRAVEL_PORTAL_H
