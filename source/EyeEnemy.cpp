#include "EyeEnemy.h"

namespace gcore
{
	EyeEnemy::EyeEnemy()
	{
		maxHealth = 300;
		currentHealth = 300;

		SpriteSheet enemy_idleSheet(16, 16, 5, "vendor/eye_enemy_idle.png");

		Animation enemy_idleAnim("idle", enemy_idleSheet, true, 4, 0.25f, true);

		animator.AddAnimation(enemy_idleAnim);

		animator.Play("idle");
	}
}
