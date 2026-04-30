#pragma once

#include "SFML/Audio.hpp"

namespace gcore
{
	class SoundManager
	{
	public:
		sf::Sound* currentSound;
		sf::Sound* currentSound2;
		bool soundShouldStop;

		sf::Sound healSound;
		sf::SoundBuffer healSoundBuff;

		sf::Sound pickupSound;
		sf::SoundBuffer pickupSoundBuff;

		sf::Sound hurtSound;
		sf::SoundBuffer hurtSoundBuff;

		SoundManager();

		void Tick(float deltaTime);
		void PlaySound(sf::Sound* sound, sf::SoundBuffer* soundBuffer);
		void PlaySoundOnSecond(sf::Sound* sound, sf::SoundBuffer* soundBuffer);
		void StopSound();
	};
}