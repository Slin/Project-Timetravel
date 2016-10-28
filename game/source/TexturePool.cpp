//
// Created by gclmini-06 on 06.11.2015.
//

#include "TexturePool.h"
#include "World.h"

namespace TT
{
	TexturePool *TexturePool::_instance = 0;

	TexturePool::TexturePool()
	{

	}

	sf::Texture *TexturePool::GetTexture(std::string textureName)
	{

		if(_textureMap.find(textureName)==_textureMap.end())
		{
			LoadTexture(textureName);
		}

		return _textureMap.at(textureName);

	}

	void TexturePool::LoadTexture(std::string textureName)
	{
		sf::Texture *texture;
		texture = new sf::Texture();//
		texture->loadFromFile(World::GetInstance()->GetBundlePath()+textureName);
		texture->setSmooth(true);
		_textureMap.insert(std::pair<std::string, sf::Texture *>(textureName, texture));
	}

	TexturePool *TexturePool::GetInstance()
	{
		if(!_instance)
			_instance = new TexturePool();

		return _instance;
	}
}