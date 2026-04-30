#pragma once

#include "SpriteSheet.h"
#include "Animator.h"

namespace gcore
{
	class Entity
	{
	public:
		float xPos;
		float yPos;
		bool freeAllocation = false;

		int maxHealth;
		int currentHealth;
		bool onHitAnim;
		float hitAnimTimer;
		float knockForce;
		sf::Vector2f knockDirection;
		sf::Color initialColorMultiplier;

		float hpbarOffsetX;
		float hpbarOffsetY;

		sf::Color colorMultiplier;

		Animator animator;

	public:
		Entity();
		virtual ~Entity() = default;

		virtual void Tick(float deltaTime);
		virtual void CheckCollision() {};
		virtual void TakeDamage(int damage, sf::Vector2f hitDir, float knockMultiplier);
		virtual void Heal(int amount) {}
	};
}