#include "SkullEnemy.h"

namespace gcore
{
	SkullEnemy::SkullEnemy()
	{
		maxHealth = 150;
		currentHealth = 150;
		movementSpeed = 150;

		SpriteSheet enemy_idleSheet(16, 16, 5, "vendor/skull_enemy_idle.png");

		Animation enemy_idleAnim("idle", enemy_idleSheet, true, 4, 0.25f, true);

		animator.AddAnimation(enemy_idleAnim);

		animator.Play("idle");
	}
}
