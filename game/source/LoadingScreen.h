
#ifndef TIMETRAVEL_LOADINGSCREEN_H
#define TIMETRAVEL_LOADINGSCREEN_H
#include "Widget.h"
#include "SFML/Graphics/RectangleShape.hpp"

namespace TT
{
	class LoadingScreen : public Widget
	{
	public:

		static LoadingScreen *GetInstance();
		~LoadingScreen();
		LoadingScreen(float speed);
		void Update(float timeStep);
		void OnGUI(sf::RenderWindow *window);
		void Draw(sf::RenderWindow *window);
		bool Fadein();
		void Fadeout();
		bool isLoading();
		bool isFinished();
	private:
		sf::RectangleShape rectangle;
		float _speed;
		float _alpha;
		bool fadingin;
		bool fadingout;
		bool isfinished;
		static LoadingScreen *_instance;
	};
}

#endif