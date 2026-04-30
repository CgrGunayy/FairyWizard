#include "Game.h"

static int randomInt(int a, int b)
{
	if (a > b)
		return randomInt(b, a);
	if (a == b)
		return a;
	return a + (rand() % (b - a));
}

void Game::Setup()
{
	backgroundColor = sf::Color(205, 177, 214);

	physics.tickrate = 60;
	physics.AddCollider(&player.collider);
	player.xPos = 350;
	player.yPos = 350;

	gcore::Animation flamethrowerAnim = gcore::Animation("idle", gcore::SpriteSheet(8, 8, 5, "vendor/projectile.png"), true, 2, 0.15f, true);
	gcore::Animation energyBallAnim = gcore::Animation("idle", gcore::SpriteSheet(16, 16, 3, "vendor/big_projectile.png"), true, 2, 0.05f, true);
	gcore::Animation starDustAnim = gcore::Animation("idle", gcore::SpriteSheet(8, 8, 3, "vendor/stardust.png"), true, 2, 0.1f, true);
	gcore::Animation grassAnim = gcore::Animation("idle", gcore::SpriteSheet(8, 8, 5, "vendor/grass_projectile.png"), true, 2, 0.15f, true);
	gcore::Animation bloodAnim = gcore::Animation("idle", gcore::SpriteSheet(8, 8, 5, "vendor/blood_projectile.png"), true, 2, 0.15f, true);
	gcore::Animation deathRayAnim = gcore::Animation("idle", gcore::SpriteSheet(8, 8, 3, "vendor/deathray_projectile.png"), true, 1, 1.0f, true);
	gcore::Animation smokeAnim = gcore::Animation("idle", gcore::SpriteSheet(32, 32, 3, "vendor/smoke.png"), true, 2, 1.0f, true);

	magicWands.insert(std::pair<const char*, gcore::Wand>("flamethrower",
		gcore::Wand(0.05f, 500, 1.0f, 0.8f, 18, 24, false, 16, 16, "vendor/flamethrower.wav", flamethrowerAnim, sf::Color(232, 170, 0, 200))));

	magicWands.insert(std::pair<const char*, gcore::Wand>("stardust",
		gcore::Wand(0.1f, 800, 1.0f, 3.0f, 32, 48, true, 16, 16, "vendor/stardust.wav", starDustAnim, sf::Color(220, 220, 255, 255))));

	magicWands.insert(std::pair<const char*, gcore::Wand>("energyball",
		gcore::Wand(1.0f, 200, 2.0f, 1.0f, 48, 72, false, 32, 32, "vendor/energyball.wav", energyBallAnim, sf::Color(0, 170, 232, 200))));

	magicWands.insert(std::pair<const char*, gcore::Wand>("nature's gift",
		gcore::Wand(0.05f, 300, 2.0f, -5.0f, 48, 72, false, 32, 32, "vendor/grass.wav", grassAnim, sf::Color(255, 255, 255, 255))));

	magicWands.insert(std::pair<const char*, gcore::Wand>("satan's sacrifice",
		gcore::Wand(0.075f, 150, 2.0f, 0, 48, 72, false, 32, 32, "vendor/blood.wav", bloodAnim, sf::Color(255, 255, 255, 255))));

	magicWands.insert(std::pair<const char*, gcore::Wand>("death ray",
		gcore::Wand(1.5f, 1000, 2.0f, 5.0f, 150, 196, false, 32, 32, "vendor/deathray.wav", deathRayAnim, sf::Color(220, 20, 20, 255))));

	magicWands.insert(std::pair<const char*, gcore::Wand>("electric smoke",
		gcore::Wand(0.5f, 100, 4.0f, 0.0f, 32, 64, false, 64, 64, "vendor/smoke.wav", smokeAnim, sf::Color(50, 150, 200, 175))));


	ui.PopupString("First Wave", 48, 2.0f, 300, 100);
	for (int i = 0; i < waves[currentWaveIndex]; i++)
	{
		gcore::EyeEnemy* enemy = new gcore::EyeEnemy();
		Summon(enemy, randomInt(-200, 1000), randomInt(-100, 800));
	}

	for (auto const& imap : magicWands)
		magicWandNames.push_back(imap.first);
}

void Game::Run(float deltaTime)
{
	soundManager.Tick(deltaTime);

	for (auto& popup : ui.popupList)
	{
		popup.timer -= deltaTime;
		sf::Vector2f pos = popup.text.getPosition();
		popup.text.setPosition(pos.x - 50 * deltaTime, pos.y - 80 * deltaTime);
	}

	if (respawning)
	{
		if (respawnClock.getElapsedTime().asSeconds() >= 1.0f)
		{
			ui.PopupNumber(timeToRespawn, 48, 1.0f, 400, 150);
			timeToRespawn -= 1;
			respawnClock.restart();

			if (timeToRespawn <= 0)
				Respawn();
		}
		return;
	}

	FreeOutdatedEntities();

	physics.Tick();

	player.Tick(deltaTime);

	for (auto& ent : spawnedEntities)
	{
		if (ent != nullptr && ent->freeAllocation == false)
		{
			ent->Tick(deltaTime);
			ent->CheckCollision();
		}
	}
}

void RenderEntity(gcore::Entity& ent, sf::RenderWindow* window)
{
	sf::Sprite& sp = ent.animator.GetCurrentSprite();
	sp.setPosition(ent.xPos, ent.yPos);
	sp.setColor(ent.colorMultiplier);
	window->draw(sp);
}

void Game::Render(sf::RenderWindow* window)
{
	window->clear(backgroundColor);

	if (respawning == false)
		RenderEntity(player, window);

	for (auto& ent : spawnedEntities)
	{
		RenderEntity(*ent, window);
	}

	sf::Event event;
	if (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
			renderColliders = !renderColliders;
	}

	if (renderColliders)
		physics.Render(window);

	ui.Render(player, window);
}

void Game::OnPlayerDied()
{
	for (auto& ent : spawnedEntities)
	{
		ent->freeAllocation = true;
	}

	timeToRespawn = 3;
	respawning = true;

	currentWaveIndex = 0;
	FreeOutdatedEntities();

	player.stop = true;
	ui.PopupString("DIED", 48, 0.9f, 300, 100);
	ui.PopupString("RESPAWNING IN 3 SEC", 48, 0.9f, 100, 150);
	respawnClock.restart();
}

void Game::Respawn()
{
	respawning = false;
	player.currentHealth = player.maxHealth;
	player.xPos = 300;
	player.yPos = 300;
	player.stop = false;
	respawnClock.restart();

	ui.PopupString("First Wave", 48, 2.0f, 300, 100);
	for (int i = 0; i < waves[currentWaveIndex]; i++)
	{
		gcore::EyeEnemy* enemy = new gcore::EyeEnemy();
		Summon(enemy, randomInt(-200, 1000), randomInt(-100, 800));
	}
}

void Game::NewWave()
{
	currentWaveIndex++;
	ui.PopupString("Next Wave", 48, 2.0f, 300, 100);
	for (int i = 0; i < waves[currentWaveIndex]; i++)
	{
		int rand = randomInt(0, 2);
		if (rand == 0)
		{
			gcore::EyeEnemy* enemy = new gcore::EyeEnemy();
			Summon(enemy, randomInt(-200, 1000), randomInt(-100, 800));
		}
		else
		{
			gcore::SkullEnemy* enemy = new gcore::SkullEnemy();
			Summon(enemy, randomInt(-200, 1000), randomInt(-100, 800));
		}
	}
}

void Game::Summon(gcore::Entity* entity, float xPos, float yPos)
{
	std::shared_ptr<gcore::Entity> po(entity);
	spawnedEntities.push_back(po);
	entity->xPos = xPos;
	entity->yPos = yPos;
}

void Game::FreeOutdatedEntities()
{
	spawnedEntities.erase(std::remove_if(spawnedEntities.begin(), spawnedEntities.end(), [](std::shared_ptr<gcore::Entity> const& val) { return val->freeAllocation == true; }), spawnedEntities.end());
	
	if(respawning)
	return;

	int enemyCount = std::count_if(spawnedEntities.begin(), spawnedEntities.end(), [](std::shared_ptr<gcore::Entity> const& val) { return val->maxHealth > 0; });
	if (enemyCount <= 0)
	{
		NewWave();
	}
}