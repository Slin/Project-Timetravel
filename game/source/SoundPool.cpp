//
// Created by gclmini-06 on 07.11.2015.
//

#include "SoundPool.h"
#include <random>
namespace TT
{

	SoundPool *SoundPool::_instance = 0;

	SoundPool::SoundPool()
	{
		LoadSound("assets/sounds/explosion.ogg");
	}


	void SoundPool::LoadSound(std::string sound)
	{
		sf::SoundBuffer* buf = new sf::SoundBuffer();
		buf->loadFromFile(World::GetInstance()->GetBundlePath()+sound);
		soundMap.insert(std::pair<std::string,sf::SoundBuffer*>(sound,buf));
	}
	sf::SoundBuffer *SoundPool::GetSound(std::string sound)
	{
		if(soundMap.find(sound)==soundMap.end()){
			LoadSound(sound);
		}
		return soundMap.at(sound);
	}

	SoundPool *SoundPool::GetInstance()
	{
		if(!_instance)
			_instance = new SoundPool();

		return _instance;
	}

	SoundPool::~SoundPool()
	{
		soundMap.clear();
	}

}