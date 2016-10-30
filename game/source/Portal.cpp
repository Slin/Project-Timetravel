//
// Created by Nils Daumann on 30.10.16.
//

#include "PlayerEntity.h"
#include "Cutscene.h"
#include "Portal.h"
#include "World.h"

namespace TT
{
	Portal::Portal(sf::Vector2f position) : Actor(position, "assets/textures/level_3/portal.png",  b2_kinematicBody, true, sf::Vector2f(1.0f, 1.0f), sf::Vector2f(436.0f, 482.0f)), _time(0.0f)
	{
		canInteract = false;
		hidden = true;

		const std::string vertexShader = \
				"void main()"\
				"{"\
				"   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"\
				"   gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"\
				"   gl_FrontColor = gl_Color;"\
				"}";

		const std::string fragmentShader = \
				"uniform sampler2D texture;"\
				"uniform float time;"\
                "void main()"\
				"{"\
				"   vec2 texcoords = gl_TexCoord[0].xy;"\
				"   texcoords.y += sin(time*5.0+texcoords.x*30.0)*0.01;"\
				"   vec4 color = texture2D(texture, texcoords);"\
				"   gl_FragColor = gl_Color * color;"\
				"}";

		if(!_shader.loadFromMemory(vertexShader, fragmentShader))
		{
			// error...
		}
	}

	Portal::~Portal()
	{

	}

	void Portal::Update(float timeStep)
	{
		_time += timeStep;

		canInteract = World::KEYS[2];
		hidden = !canInteract;
	}

	void Portal::Draw(sf::RenderWindow *window) {
		if (!hidden) {
			_shader.setUniform("time", _time);
			window->draw(*_object, &_shader);
		}
	}

	void Portal::OnInteract(Entity *interactor) {
		Actor::OnInteract(interactor);

		if(World::KEYS[2]) {
			World::GetInstance()->GetPlayer()->PlayPickupSound();
			Cutscene::GetInstance()->StartCutscene(2);
		}
	}
}