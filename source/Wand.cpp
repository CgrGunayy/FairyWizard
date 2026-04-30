#include "Wand.h"

namespace gcore
{
	Wand::Wand(float fireInterval, float projSpeed, float projLifetime, float knockbackMultiplier, int minDamage, int maxDamage, bool destroyOnColl, int collWidth, int collHeight, const char* audioPath, const Animation& projectileAnim, const sf::Color& projectileColor)
		: projSpawnInterval(fireInterval), projSpeed(projSpeed), projLifetime(projLifetime), knockbackMultiplier(knockbackMultiplier), minDamage(minDamage), maxDamage(maxDamage), destroyProjOnColl(destroyOnColl), colliderWidth(collWidth), colliderHeight(collHeight), projectileAnim(projectileAnim), projectileColor(projectileColor)
	{
		if (!soundBuffer.loadFromFile(audioPath))
			printf("Sound couldn't be found!");
	}


}