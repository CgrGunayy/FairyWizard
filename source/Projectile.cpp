#include "Projectile.h"
#include "Game.h"
#include "Math.h"

extern Game* game;

namespace gcore
{
	Projectile::Projectile(sf::Vector2f dir, float speed, int minDamage, int maxDamage, float maxLifetime, float knockMultiplier, bool destroyOnCollision)
		: direction(dir), speed(speed), minDamage(minDamage), maxDamage(maxDamage), currentLifetime(0), maxLifetime(maxLifetime), knockMultiplier(knockMultiplier),
		  destroyOnCollision(destroyOnCollision), collider(this, ColliderType::Projectile, {}, 4, 4, 16, 16)
	{
		game->physics.AddCollider(&collider);
	}

	Projectile::~Projectile()
	{
		game->physics.RemoveCollider(&collider);
	}

	void Projectile::Tick(float deltaTime)
	{
		Entity::Tick(deltaTime);

		collider.xPos = xPos;
		collider.yPos = yPos;

		xPos += direction.x * speed * deltaTime;
		yPos += direction.y * speed * deltaTime;

		currentLifetime += deltaTime;

		if (currentLifetime >= maxLifetime)
			freeAllocation = true;
		else
			colorMultiplier.a = 255 - (currentLifetime / maxLifetime) * 255;
	}

	static int randomInt(int a, int b)
	{
		if (a > b)
			return randomInt(b, a);
		if (a == b)
			return a;
		return a + (rand() % (b - a));
	}

	void Projectile::CheckCollision()
	{
		if (collider.collisions.size() > 0 && freeAllocation != true)
		{
			for (auto& coll : collider.collisions)
			{
				if (coll != nullptr && coll->ownerEntity->onHitAnim == false)
				{
					sf::Vector2f hitDir(coll->xPos - xPos, coll->yPos - yPos);
					float length = sqrt(hitDir.x * hitDir.x + hitDir.y * hitDir.y);

					sf::Vector2f normalizedDir;
					if (length == 0)
						normalizedDir = hitDir;
					else
						normalizedDir = hitDir / length;


					int damage = randomInt(minDamage, maxDamage);
					coll->ownerEntity->TakeDamage(damage, normalizedDir, knockMultiplier);

					if (destroyOnCollision)
					{
						freeAllocation = true;
						break;
					}
				}
			}
		}
	}
}