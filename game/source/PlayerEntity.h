//
// Created by Nils Daumann on 17.08.16.
//

#ifndef TIMETRAVEL_PLAYERENTITY_H
#define TIMETRAVEL_PLAYERENTITY_H

#include "World.h"

namespace TT
{
	class PlayerEntity : public Entity, public b2QueryCallback
	{
	public:

		bool _disabled = false;

		PlayerEntity(sf::Vector2f position);
		~PlayerEntity();

		void Update(float timeStep);
		void Interpolate(float factor);
		void Draw(sf::RenderWindow *window);

		bool IsGrounded();

		bool ReportFixture(b2Fixture* fixture);

		void TriggerInteraction();

		void PlayPickupSound();
		void StopPlayingWalking();
		void PlayWalkingSounds();

		int level;
	private:
		sf::Sprite *_object;
		b2Body *_body;
		b2Fixture *_boxFixture;

		float _animationTimer;
		void FindInteractionObjects();
        Actor* _interactionTarget;
		int sound_counter;
		sf::Sound _pickupSound;
		sf::Sound _walkingSoundForest;
		sf::Sound _walkingSoundCave[7];
		sf::Sound _walkingSoundLibrary[4];
	};
}

#endif //TIMETRAVEL_PLAYERENTITY_H
