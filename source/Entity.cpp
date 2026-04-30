#include "Entity.h"

namespace gcore
{
	Entity::Entity() : xPos(0), yPos(0), currentHealth(0), maxHealth(0), hpbarOffsetX(0), hpbarOffsetY(0), knockForce(30), onHitAnim(false), hitAnimTimer(0.75f), colorMultiplier(sf::Color(255, 255, 255, 255))
	{
		initialColorMultiplier = colorMultiplier;
	}

	void Entity::Tick(float deltaTime)
	{
		animator.Tick(deltaTime);

		if (onHitAnim && hitAnimTimer > 0)
		{
			xPos += knockForce * deltaTime * knockDirection.x;
			yPos += knockForce * deltaTime * knockDirection.y;
			hitAnimTimer -= deltaTime;
		}

		if (hitAnimTimer <= 0)
		{
			colorMultiplier = initialColorMultiplier;
			animator.stop = false;
			onHitAnim = false;
		}
	}

	void Entity::TakeDamage(int damage, sf::Vector2f hitDir, float knockMultiplier)
	{
		colorMultiplier = sf::Color(255, 0, 0, 200);
		knockDirection = hitDir * knockMultiplier;
		hitAnimTimer = 0.3f;
		animator.stop = true;
		onHitAnim = true;
	}
}