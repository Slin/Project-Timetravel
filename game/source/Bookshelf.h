//
// Created by Nils Daumann on 30.10.16.
//

#ifndef TIMETRAVEL_BOOKSHELF_H
#define TIMETRAVEL_BOOKSHELF_H

#include "Actor.h"

namespace TT
{
	class Bookshelf : public Actor
	{
	public:
		Bookshelf(int id, sf::Vector2f position);
		~Bookshelf();

		void Update(float timestep);
		void Draw(sf::RenderWindow *_window);

		void OnBlur(Entity *interactor);
		void OnFocus(Entity *interactor);
		void OnInteract(Entity *interactor);

	private:
		void StartGlow();
		void StopGlow();

		static int _activeCounter;

		int _id;
		sf::Sprite *_glow;
	};
}

#endif //TIMETRAVEL_BOOKSHELF_H
