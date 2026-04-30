#pragma once

#include "Entity.h"
#include "Physics.h"

namespace gcore
{
	class Projectile : public Entity
	{
	private:
		sf::Vector2f direction;
		float speed;
		float maxLifetime;
		float currentLifetime;
		float knockMultiplier;
		bool destroyOnCollision;

		int minDamage;
		int maxDamage;

	public:
		Collider collider;

		Projectile(sf::Vector2f dir, float speed, int minDamage, int maxDamage, float maxLifetime, float knockMutliplier, bool destoryOnCollision);
		~Projectile();

		void Tick(float deltaTime);
		void CheckCollision();
	};
}