#pragma once

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Entity.h"

namespace gcore
{
	enum class ColliderType
	{
		Default,
		Player,
		Enemy,
		Projectile
	};

	class Collider
	{
	public:
		float xPos;
		float yPos;
		float xOffset;
		float yOffset;
		float width;
		float height;

		Entity* ownerEntity;

		ColliderType colliderType;
		std::vector<ColliderType> targetColliders;

		std::vector<Collider*> collisions;

		Collider(Entity* owner, ColliderType colliderType, std::vector<ColliderType> targetColliders, float xOffset, float yOffset, float width, float height)
			: xPos(0), yPos(0), ownerEntity(owner), colliderType(colliderType), targetColliders(targetColliders), xOffset(xOffset), yOffset(yOffset), width(width), height(height)
		{}
	};

	class Physics
	{
	private:
		sf::Clock clock;
		std::vector<Collider*> colliders; 
	public:
		float tickrate;

		void Tick();
		void AddCollider(gcore::Collider* coll);
		void RemoveCollider(gcore::Collider* coll);
		void Render(sf::RenderWindow* window);
	};
}