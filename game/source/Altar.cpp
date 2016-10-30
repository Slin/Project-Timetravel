//
// Created by Nils Daumann on 29.10.16.
//

#include "Altar.h"
#include "Dialog.h"
#include "PlayerEntity.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace TT
{
	int Altar::_activeCounter = 0;

	Altar::Altar(int id, sf::Vector2f position) : Actor(position, "assets/textures/none.png", b2_kinematicBody, true), _id(id), _glow(nullptr), _finalGlow(nullptr), _timer(0.0f)
	{
        if (World::KEYS[1])
        {
            StartGlow();
            Altar::_activeCounter = 3;
            canInteract = false;
        } else
        {
            canInteract = true;
        }

        hidden = true;

        if (id == 0)
        {
            _sound.setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/level_2/altar_pulse_00.ogg"));
        }
        if (id == 1)
        {
            _sound.setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/level_2/altar_pulse_01.ogg"));
        }
        if (id == 2)
        {
            _sound.setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/level_2/altar_pulse_02.ogg"));
        }
		_sound.setLoop(true);
        _sound.setVolume(25.0f);
	}

	Altar::~Altar()
	{
		delete _glow;
	}

	void Altar::Update(float timeStep)
	{
		Actor::Update(timeStep);

		_timer += timeStep*5.0f;
		if(_timer >= M_PI*2.0f)
		{
			_timer -= M_PI*2.0f;

			if(_glow && !_finalGlow && _id == 2)
			{
				_finalGlow = World::CreateSprite("assets/textures/level_2/glowall.png");
				_finalGlow->setPosition(sf::Vector2f(3411 - 0.5*1920, 218));
			}
		}

		if(Altar::_activeCounter == 0 && canInteract)
		{
			StopGlow();
		}

        if(Altar::_activeCounter - 1 != _id)
        {
            if(_sound.getStatus() != sf::SoundSource::Stopped)
            {
                _sound.stop();
            }
        }

		if(_glow)
		{
			_glow->setColor(sf::Color(255, 255, 255, 255.0f*(sinf(_timer)*0.4f+0.6f)));
		}

		if(_finalGlow)
		{
			_finalGlow->setColor(sf::Color(255, 255, 255, 255.0f*(sinf(_timer)*0.3f+0.3f)));
		}
	}

	void Altar::Draw(sf::RenderWindow *window)
	{
		Actor::Draw(window);

		sf::RenderStates renderStates = sf::RenderStates::Default;
		renderStates.blendMode = sf::BlendAdd;

		if(_glow)
			window->draw(*_glow, renderStates);

		if(_finalGlow)
			window->draw(*_finalGlow, renderStates);
	}

	void Altar::OnBlur(Entity *interactor)
	{
		Actor::OnBlur(interactor);
		_spriteIndex = 0;
	}

	void Altar::OnFocus(Entity *interactor)
	{
		Actor::OnFocus(interactor);
		_spriteIndex = 1;
	}

	void Altar::OnInteract(Entity *interactor)
	{
		Actor::OnInteract(interactor);

		if(World::KEYS[1])
			return;

		if(_id == Altar::_activeCounter)
		{
			Altar::_activeCounter += 1;
			StartGlow();

			if(_id == 2)
			{
				World::KEYS[1] = true;
				canInteract = false;
				Dialog::GetInstance()->SetText("You feel as if something changed inside you.");
				Dialog::GetInstance()->SetResetTimer(5.0f);
				World::GetInstance()->GetPlayer()->PlayPickupSound();
			}
		}
		else
		{
			Altar::_activeCounter = 0;
		}
	}

	void Altar::StartGlow()
	{
		if(_glow)
			return;

		if(_id == 0)
		{
			_glow = World::CreateSprite("assets/textures/level_2/glow1.png");
			_glow->setPosition(sf::Vector2f(3245 - 0.5*1920, 218));
		}
		if(_id == 2)
		{
			_glow = World::CreateSprite("assets/textures/level_2/glow2.png");
			_glow->setPosition(sf::Vector2f(3411 - 0.5*1920, 219));
		}
		if(_id == 1)
		{
			_glow = World::CreateSprite("assets/textures/level_2/glow3.png");
			_glow->setPosition(sf::Vector2f(3580 - 0.5*1920, 215));
		}

        _sound.play();
	}

	void Altar::StopGlow()
	{
		if(!_glow)
		{
            _sound.stop();
            return;
        }

		delete _glow;
		_glow = nullptr;
	}
}
