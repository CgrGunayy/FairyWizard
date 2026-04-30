#include "Game.h"
#include "Projectile.h"

#include <iostream>

extern sf::RenderWindow* window;
extern Game* game;

namespace gcore
{
	Player::Player()
		: movementSpeed(150),
		projSpawnTimer(0),
		stop(false),
		collider(this, ColliderType::Player, {}, 16, 16, 48, 48),
		currentWandName("energyball"),
		targetColliders({ ColliderType::Enemy })
	{
		maxHealth = 100;
		currentHealth = 100;
		knockForce = 80;

		SpriteSheet player_idleSheet(16, 16, 5, "vendor/player_idle.png");
		SpriteSheet player_walkSheet(16, 16, 5, "vendor/player_walk.png");

		Animation player_idleAnim("idle", player_idleSheet, true, 4, 0.25f, true);
		Animation player_walkAnim("walk", player_walkSheet, true, 2, 0.35f, true);

		animator.AddAnimation(player_idleAnim);
		animator.AddAnimation(player_walkAnim);

		animator.Play("idle");
	}

	void Player::Tick(float deltaTime)
	{
		Entity::Tick(deltaTime);

		if (!stop)
			Movement(deltaTime);

		collider.xPos = xPos;
		collider.yPos = yPos;

		if (projSpawnTimer > 0)
			projSpawnTimer -= deltaTime;

		Wand& wand = game->magicWands[currentWandName];

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && projSpawnTimer <= 0)
		{
			game->soundManager.PlaySound(&wand.sound, &wand.soundBuffer);

			projSpawnTimer = wand.projSpawnInterval;
			sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
			sf::Vector2f mousePos(localPosition.x, localPosition.y);
			sf::Vector2f origin(xPos + 30, yPos - 8);
			sf::Vector2f direction = mousePos - origin;

			float length = sqrt(direction.x * direction.x + direction.y * direction.y);
			sf::Vector2f normalizedDir = direction / length;

			float randomOffsetX = 8 * (rand() % 2 - 1);
			float randomOffsetY = 8 * (rand() % 2 - 1);

			Projectile* proj = new Projectile(normalizedDir, wand.projSpeed, wand.minDamage, wand.maxDamage, wand.projLifetime, wand.knockbackMultiplier, wand.destroyProjOnColl);
			proj->collider.targetColliders = targetColliders;
			proj->collider.width = wand.colliderWidth;
			proj->collider.height = wand.colliderHeight;
			proj->animator.AddAnimation(wand.projectileAnim);
			proj->colorMultiplier = wand.projectileColor;
			game->Summon(proj, origin.x + randomOffsetX, origin.y + randomOffsetY);
			proj->animator.Play("idle");
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			game->soundManager.StopSound();
		}
	}

	Player::~Player()
	{
		game->physics.RemoveCollider(&collider);
	}

	void Player::Movement(float deltaTime)
	{
		float xInput = sf::Keyboard::isKeyPressed(sf::Keyboard::D) ? 1.0f : sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? -1.0f : 0.0f;
		float yInput = sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? 1.0f : sf::Keyboard::isKeyPressed(sf::Keyboard::W) ? -1.0f : 0.0f;

		sf::Vector2f moveVec(xInput, yInput);
		float length = sqrt(moveVec.x * moveVec.x + moveVec.y * moveVec.y);
		if (length <= 0)
		{
			if (isMoving)
			{
				animator.Play("idle");
				isMoving = false;
			}

			return;
		}

		if (!isMoving)
			animator.Play("walk");

		isMoving = true;
		sf::Vector2f normalizedInput = moveVec / length;

		xPos += normalizedInput.x * movementSpeed * deltaTime;
		yPos += normalizedInput.y * movementSpeed * deltaTime;
	}

	static float randomFloat()
	{
		return (float)(rand()) / (float)(RAND_MAX);
	}

	void Player::TakeDamage(int damage, sf::Vector2f hitDir, float knockMultiplier)
	{
		Entity::TakeDamage(damage, hitDir, knockMultiplier);

		currentHealth -= damage;

		int randomOffsetX = 64 * randomFloat();
		int randomOffsetY = 64 * randomFloat();

		game->soundManager.PlaySoundOnSecond(&game->soundManager.hurtSound, &game->soundManager.hurtSoundBuff);
		game->ui.PopupNumber(damage, 38, 0.3f, xPos + 16 + randomOffsetX, yPos - 16 + randomOffsetY);

		if (currentHealth <= 0)
		{
			currentHealth = 0;
			game->OnPlayerDied();
		}
	}

	void Player::Heal(int amount)
	{
		currentHealth += amount;

		int randomOffsetX = 64 * randomFloat();
		int randomOffsetY = 64 * randomFloat();
		game->ui.PopupString("+", 38, 0.3f, xPos + 16 + randomOffsetX, yPos - 16 + randomOffsetY);
		if (currentHealth > maxHealth)
			currentHealth = maxHealth;
	}
}