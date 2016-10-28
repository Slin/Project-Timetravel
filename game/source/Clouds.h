
#ifndef TIMETRAVE_CLOUDS_H
#define TIMETRAVEL_CLOUDS_H
#endif

#include "Background.h"

namespace TT
{
	class Clouds : public Background
	{
	public:
		Clouds( float offsetspeed, float speed, const std::string path);
		~Clouds();
		void SetSpeed(float speed) { _speed = speed; };
		float GetOffset() { return _offset; }
		void Draw(sf::RenderWindow *window, float timeStep);

	private:
		float _offset;
		float _offsetspeed;






	};




}
