
#ifndef TIMETRAVEL_LOADINGSCREEN_H
#define TIMETRAVEL_LOADINGSCREEN_H
#include "Widget.h"
#include "SFML\Graphics\RectangleShape.hpp"

namespace TT
{
	class LoadingScreen : public Widget
	{
	public:
		LoadingScreen(float speed);
		void Update(float timeStep);
		void OnGUI(sf::RenderWindow *window);
		void Draw(sf::RenderWindow *window);
		void Fadein(float timeStep);
		void Fadeout(float timeStep);
	private:
		sf::RectangleShape rectangle;
		float _speed;
		float _alpha;
		bool fadingin;
		bool fadingout;
	};
}

#endif