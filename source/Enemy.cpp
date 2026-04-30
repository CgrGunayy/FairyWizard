#include "Enemy.h"
#include "Game.h"
#include "Math.h"

#include <iostream>

extern Game* game;

namespace gcore
{
	static int randomInt(int a, int b)
	{
		if (a > b)
			return randomInt(b, a);
		if (a == b)
			return a;
		return a + (rand() % (b - a));
	}

	Enemy::Enemy()
		: movementSpeed(80), collider(this, ColliderType::Enemy, { ColliderType::Player }, 16, 16, 48, 48), damageCooldown(1.5f), timer(1.0f), stop(true)
	{
		hpbarOffsetX = 2;
		hpbarOffsetY = -54;

		game->physics.AddCollider(&collider);
		game->ui.CreateHealthBar(this);
	}

	Enemy::~Enemy()
	{
		game->physics.RemoveCollider(&collider);
		game->ui.RemoveHealthBar(this);
	}

	void Enemy::Tick(float deltaTime)
	{
		Entity::Tick(deltaTime);

		collider.xPos = xPos;
		collider.yPos = yPos;

		if (timer > 0)
			timer -= deltaTime;
		else
			stop = false;

		if (stop)
			return;

		Movement(deltaTime);
	}

	void Enemy::Movement(float deltaTime)
	{
		float playerX = game->player.xPos;
		float playerY = game->player.yPos;

		sf::Vector2f dir(playerX - xPos, playerY - yPos);
		float length = sqrt(dir.x * dir.x + dir.y * dir.y);

		sf::Vector2f normDir = dir;
		if (length > 0)
			normDir = dir / length;

		xPos += normDir.x * movementSpeed * deltaTime;
		yPos += normDir.y * movementSpeed * deltaTime;
	}

	static float randomFloat()
	{
		return (float)(rand()) / (float)(RAND_MAX);
	}

	void Enemy::TakeDamage(int damage, sf::Vector2f hitDir, float knockMultiplier)
	{
		Entity::TakeDamage(damage, hitDir, knockMultiplier);

		currentHealth -= damage;

		int randomOffsetX = 64 * randomFloat();
		int randomOffsetY = 64 * randomFloat();
		game->ui.PopupNumber(damage, 38, 0.3f, xPos + 16 + randomOffsetX, yPos - 16 + randomOffsetY);

		if (currentHealth <= 0)
		{
			currentHealth = 0;
			int rand = randomInt(0, 10);
			if (rand == 0 || rand == 5 || rand == 6) // %30 chance
			{
				int randomWand = randomInt(0, game->magicWands.size());
				gcore::WandPickup* wand = new gcore::WandPickup();
				wand->wandName = game->magicWandNames[randomWand];
				game->Summon(wand, xPos, yPos);
			}
			else if (rand == 1 || rand == 2 || rand == 3 || rand == 4) // %40 chance
			{
				HealthPack* healthPack = new HealthPack();
				game->Summon(healthPack, xPos, yPos);
			}

			freeAllocation = true;
		}
	}

	void Enemy::CheckCollision()
	{
		if (collider.collisions.size() > 0)
		{
			for (auto& coll : collider.collisions)
			{
				if (coll != nullptr && !stop)
				{
					sf::Vector2f hitDir(coll->xPos - xPos, coll->yPos - yPos);
					float length = sqrt(hitDir.x * hitDir.x + hitDir.y * hitDir.y);

					sf::Vector2f normalizedDir;
					if (length == 0)
						normalizedDir = hitDir;
					else
						normalizedDir = hitDir / length;

					stop = true;
					timer = damageCooldown;
					int damage = randomInt(25, 35);
					coll->ownerEntity->TakeDamage(damage, normalizedDir, 1.25f);
				}
			}
		}
	}
}