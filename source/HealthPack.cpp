#include "HealthPack.h"
#include "Game.h"

extern Game* game;

namespace gcore
{
	HealthPack::HealthPack() : healAmount(10), lifetime(5.0f), timer(5.0f), collider(this, ColliderType::Default, { ColliderType::Player }, 16, 16, 48, 48)
	{
		SpriteSheet healthpack_idleSheet(16, 16, 5, "vendor/health_pack.png");
		Animation healthpack_idleAnim("idle", healthpack_idleSheet, true, 4, 0.2f, true);

		animator.AddAnimation(healthpack_idleAnim);

		animator.Play("idle");

		game->physics.AddCollider(&collider);
	}

	HealthPack::~HealthPack()
	{
		game->physics.RemoveCollider(&collider);
	}

	void HealthPack::Tick(float deltaTime)
	{
		Entity::Tick(deltaTime);

		collider.xPos = xPos;
		collider.yPos = yPos;

		if (timer > 0)
		{
			timer -= deltaTime;
			colorMultiplier.a = (timer / lifetime) * 255;
		}
		else
			freeAllocation = true;
	}

	void HealthPack::CheckCollision()
	{
		if (collider.collisions.size() > 0 && freeAllocation != true)
		{
			for (auto& coll : collider.collisions)
			{
				if (coll != nullptr)
				{
					coll->ownerEntity->Heal(healAmount);
					game->soundManager.PlaySoundOnSecond(&game->soundManager.healSound, &game->soundManager.healSoundBuff);
					freeAllocation = true;
					break;
				}
			}
		}
	}
}