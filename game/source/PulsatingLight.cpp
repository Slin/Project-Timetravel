//
// Created by Nils Daumann on 30.10.16.
//

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "PulsatingLight.h"
#include "World.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif 


namespace TT
{
	PulsatingLight::PulsatingLight(std::string filename, sf::Vector2f position, float speed, float range) : _speed(speed), _range(range), _time(0.0f)
	{
		_object = World::GetInstance()->CreateSprite(filename);
		_object->setPosition(position);
	}

	PulsatingLight::~PulsatingLight()
	{
		delete _object;
	}

	void PulsatingLight::Update(float timeStep)
	{
		_time += timeStep*_speed;
		if(_time >= M_PI*2.0f)
			_time -= M_PI*2.0f;
		_object->setColor(sf::Color(255, 255, 255, 255.0f*(sinf(_time)*_range+(1.0f-_range))));
	}

	void PulsatingLight::Interpolate(float factor)
	{

	}

	void PulsatingLight::Draw(sf::RenderWindow *window)
	{
		sf::RenderStates renderStates = sf::RenderStates::Default;
		renderStates.blendMode = sf::BlendAdd;
		window->draw(*_object, renderStates);
	}
}
