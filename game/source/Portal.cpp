//
// Created by Nils Daumann on 30.10.16.
//

#include "Portal.h"
#include "World.h"

namespace TT
{
	Portal::Portal(sf::Vector2f position) : Actor(position, "assets/textures/level_3/portal.png",  b2_kinematicBody, true, sf::Vector2f(1.0f, 1.0f), sf::Vector2f(436.0f, 482.0f))
	{
		const std::string vertexShader = \
				"void main()"\
				"{"\
				"   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"\
				"   gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"\
				"   gl_FrontColor = gl_Color;"\
				"}";

		const std::string fragmentShader = \
				"uniform sampler2D texture;"\
                "void main()"\
				"{"\
				"   vec4 color = texture2D(texture, gl_TexCoord[0].xy);"\
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

	}

	void Portal::Draw(sf::RenderWindow *window)
	{
		window->draw(*_object, &_shader);
	}
}