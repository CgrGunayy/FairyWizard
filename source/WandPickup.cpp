#include "WandPickup.h"
#include "Game.h"

extern Game* game;

namespace gcore
{
	WandPickup::WandPickup() : wandName(""), lifetime(5.0f), timer(5.0f), collider(this, ColliderType::Default, {ColliderType::Player}, 16, 16, 48, 48)
	{
		SpriteSheet wand_idleSheet(16, 16, 5, "vendor/wand_pickup.png");
		Animation wand_idleAnim("idle", wand_idleSheet, true, 1, 1.0f, true);

		animator.AddAnimation(wand_idleAnim);

		animator.Play("idle");

		game->physics.AddCollider(&collider);
	}

	WandPickup::~WandPickup()
	{
		game->physics.RemoveCollider(&collider);
	}

	void WandPickup::Tick(float deltaTime)
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

	void WandPickup::CheckCollision()
	{
		if (collider.collisions.size() > 0 && freeAllocation != true)
		{
			for (auto& coll : collider.collisions)
			{
				if (coll != nullptr)
				{
					game->player.currentWandName = wandName;
					game->ui.PopupString(wandName, 36, 1.0f, xPos, yPos + 16);
					game->soundManager.PlaySoundOnSecond(&game->soundManager.pickupSound, &game->soundManager.pickupSoundBuff);
					freeAllocation = true;
					break;
				}
			}
		}
	}
}