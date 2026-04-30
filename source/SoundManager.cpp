#include "SoundManager.h"

namespace gcore
{

	SoundManager::SoundManager() : currentSound(nullptr), currentSound2(nullptr), soundShouldStop(false)
	{
		if (!healSoundBuff.loadFromFile("vendor/heal.wav"))
			printf("Sound couldn't be found!");

		if (!pickupSoundBuff.loadFromFile("vendor/item_pickup.wav"))
			printf("Sound couldn't be found!");

		if (!hurtSoundBuff.loadFromFile("vendor/hurt.wav"))
			printf("Sound couldn't be found!");
	}

	void SoundManager::Tick(float deltaTime)
	{
		if (soundShouldStop)
		{
			float soundVolume = currentSound->getVolume();
			soundVolume -= 100 * deltaTime;
			if (soundVolume <= 0)
			{
				currentSound->stop();
				currentSound->setVolume(100);
				soundShouldStop = false;
			}
			else
				currentSound->setVolume(soundVolume);
		}
	}

	void SoundManager::PlaySound(sf::Sound* sound, sf::SoundBuffer* soundBuffer)
	{
		if (sound->getStatus() == sf::SoundSource::Status::Playing)
			return;

		soundShouldStop = false;
		
		currentSound = sound;
		currentSound->setVolume(100);
		currentSound->setBuffer(*soundBuffer);
		currentSound->play();
	}

	void SoundManager::PlaySoundOnSecond(sf::Sound* sound, sf::SoundBuffer* soundBuffer)
	{
		if (sound->getStatus() == sf::SoundSource::Status::Playing)
			return;

		currentSound2 = sound;
		currentSound2->setVolume(100);
		currentSound2->setBuffer(*soundBuffer);
		currentSound2->play();
	}

	void SoundManager::StopSound()
	{
		if (currentSound == nullptr || currentSound->getStatus() != sf::SoundSource::Status::Playing)
			return;

		soundShouldStop = true;
	}
}