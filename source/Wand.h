#pragma once

#include "Animator.h"
#include "SFML/Audio.hpp"
#include "Physics.h"

namespace gcore
{
	class Wand
	{
	public:
		float projSpawnInterval;
		float projSpeed;
		float projLifetime;
		bool destroyProjOnColl;
		int minDamage;
		int maxDamage;
		float knockbackMultiplier;

		int colliderWidth;
		int colliderHeight;

		sf::Sound sound;
		sf::SoundBuffer soundBuffer;

		Animation projectileAnim;
		sf::Color projectileColor;

		Wand(float fireInterval, float projSpeed, float projLifetime, float knockbackMultiplier, int minDamage, int maxDamage, bool destroyOnColl, int collWidth, int collHeight, const char* audioPath, const Animation& projectileAnim, const sf::Color& projectileColor);

		Wand() : projectileAnim(Animation()), projectileColor(sf::Color()) {}
	};
}
