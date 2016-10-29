//
// Created by Nils Daumann on 30.10.16.
//

#ifndef TIMETRAVEL_PULSATINGLIGHT_H
#define TIMETRAVEL_PULSATINGLIGHT_H

#include "Entity.h"
#include "World.h"

namespace TT
{
	class PulsatingLight : public Entity
	{
	public:
		PulsatingLight(std::string filename, sf::Vector2f position, float speed, float range);
		~PulsatingLight();

		void Update(float timeStep);
		void Interpolate(float factor);
		void Draw(sf::RenderWindow *window);

	private:
		sf::Sprite *_object;
		float _time;

		float _speed;
		float _range;
	};
}


#endif //TIMETRAVEL_PULSATINGLIGHT_H
