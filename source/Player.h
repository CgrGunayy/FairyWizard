#pragma once

#include "Entity.h"
#include "Physics.h"
#include "Wand.h"

namespace gcore
{
	class Player : public Entity
	{
	public:
		float movementSpeed;
		bool isMoving = false;

		bool stop = false;

		float projSpawnTimer;

		Collider collider;
		std::vector<ColliderType> targetColliders;

		const char* currentWandName;

		Player();
		~Player();

		void Tick(float deltaTime);
		void Movement(float deltaTime);
		void TakeDamage(int damage, sf::Vector2f hitDir, float knockMultiplier);
		void Heal(int amount);
	};
}