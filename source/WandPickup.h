#pragma once
#include "Entity.h"
#include "Physics.h"

namespace gcore
{
	class WandPickup : public Entity
	{
	public:
		const char* wandName;
		float lifetime;
		float timer;

		Collider collider;

		WandPickup();
		~WandPickup();

		void Tick(float deltaTime);
		void CheckCollision();
	};
}