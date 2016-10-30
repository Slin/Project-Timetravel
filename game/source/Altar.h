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
		Altar(int id, sf::Vector2f position);
		~Altar();

		void Update(float timestep);
		void Draw(sf::RenderWindow *_window);

		void OnBlur(Entity *interactor);
		void OnFocus(Entity *interactor);
		void OnInteract(Entity *interactor);

	private:
		void StartGlow();
		void StopGlow();

		static int _activeCounter;

		float _timer;
		int _id;
		sf::Sprite *_glow;
		sf::Sprite *_finalGlow;
		sf::Sound _sound;
	};
}

#endif //TIMETRAVEL_ALTAR_H
