#pragma once

#include "Entity.h"
#include "Physics.h"
#include "SFML/Audio.hpp"

namespace gcore
{
	class HealthPack : public Entity
	{
	public:
		int healAmount;
		float lifetime;
		float timer;

		Collider collider;

		HealthPack();
		~HealthPack();

		void Tick(float deltaTime);
		void CheckCollision();
	};
}