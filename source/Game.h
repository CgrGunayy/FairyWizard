#pragma once

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Enemy.h"
#include "EyeEnemy.h"
#include "SkullEnemy.h"
#include "HealthPack.h"
#include "WandPickup.h"
#include "UserInterface.h"
#include "SoundManager.h"

class Game
{
public:
	gcore::Physics physics;
	bool renderColliders;
	UserInterface ui;
	gcore::Player player;
	gcore::SoundManager soundManager;

	std::map<const char*, gcore::Wand> magicWands;
	std::vector<const char*> magicWandNames;
private:
	sf::Clock respawnClock;
	int timeToRespawn = 3;
	bool respawning = false;


	int waves[12] = { 3, 5, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26};
	int currentWaveIndex = 0;

	sf::Color backgroundColor;
	std::vector<std::shared_ptr<gcore::Entity>> spawnedEntities;

public:

	void Setup();
	void Run(float deltaTime);
	void Render(sf::RenderWindow* window);

	void OnPlayerDied();
	void Respawn();
	
	void NewWave();

	void Summon(gcore::Entity* entity, float xPos, float yPos);
	void FreeOutdatedEntities();
};