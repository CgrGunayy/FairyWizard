#pragma once

#include "Entity.h"
#include "Physics.h"

namespace gcore
{
	class Enemy : public Entity
	{
	public:
		float movementSpeed;
		bool isMoving = false;
		bool stop = false;

		float damageCooldown;
		float timer;

		Collider collider;

		Enemy();
		~Enemy();

		void Tick(float deltaTime);
		void Movement(float deltaTime);
		void TakeDamage(int damage, sf::Vector2f hitDir, float knockMultiplier);
		void CheckCollision();
	};
}