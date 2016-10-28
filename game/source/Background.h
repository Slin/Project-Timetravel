
#ifndef TIMETRAVEL_BACKGROUND_H
#define TIMETRAVEL_BACKGROUND_H


#include "World.h"


namespace TT
{
	class Background : public Entity
	{
	public:
		Background();
		Background(float speed, const std::string path);
		~Background();
		virtual void Update(float timeStep);
		virtual void Draw(sf::RenderWindow *window);
		float GetSpeed() { return _speed; };
	protected:
		sf::Sprite *_object;
		float _speed;







	};





}
#endif