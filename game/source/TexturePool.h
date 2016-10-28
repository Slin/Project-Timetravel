//
// Created by gclmini-06 on 06.11.2015.
//

#ifndef PROJECT_SACRIFICE_TEXTUREPOOL_H
#define PROJECT_SACRIFICE_TEXTUREPOOL_H

#include <map>
#include <SFML/Graphics.hpp>


namespace TT
{
	class TexturePool
	{
		std::map<std::string,sf::Texture*> _textureMap;

	public:
		sf::Texture *GetTexture(std::string textureName);

		void LoadTexture(std::string basic_string);

		TexturePool();

		static TexturePool *_instance;

		static TexturePool *GetInstance();
	};
}


#endif //PROJECT_SACRIFICE_TEXTUREPOOL_H
