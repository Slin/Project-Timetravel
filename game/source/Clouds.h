
#ifndef TIMETRAVEL_CLOUDS_H
#define TIMETRAVEL_CLOUDS_H


#include "Background.h"

namespace TT
{
	class Clouds : public Background
	{
	public:
		Clouds( float offsetspeed, float speed, const std::string path);
		~Clouds();
		float GetOffset() { return _offset; }
		void Draw(sf::RenderWindow *window);
		void Update(float timeStep);
	private:
		float _offset;
		float xproblematic;
		float _offsetspeed;
	};
}
#endif