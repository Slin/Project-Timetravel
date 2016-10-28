//
// Created by gclmini-06 on 07.11.2015.
//

#ifndef PROJECT_SACRIFICE_SOUNDPOOL_H
#define PROJECT_SACRIFICE_SOUNDPOOL_H
#include "World.h"
#include <map>

namespace TT
{
	class SoundPool
	{
		map<std::string, sf::SoundBuffer*> soundMap;

	public:
		SoundPool();
		~SoundPool();

	private:
		void LoadSound(std::string sound);
	public:
		sf::SoundBuffer *GetSound(std::string sound);

		static SoundPool *_instance;
		static SoundPool *GetInstance();
	};
}

#endif //PROJECT_SACRIFICE_SOUNDPOOL_H
