#pragma once

#include "SFML/Graphics.hpp"
#include "SpriteSheet.h"
#include "Player.h"

class PopupText
{
public:
	sf::Text text;
	float lifeTime;
	float timer;

	PopupText(const sf::Text& text, float lifeTime)
		: text(text), lifeTime(lifeTime), timer(lifeTime)
	{}
};

class UserInterface
{
public:
	gcore::SpriteSheet wandSH;
	gcore::SpriteSheet wandOutlineSH;

	gcore::SpriteSheet healthbarFillSH;
	gcore::SpriteSheet healthbarOutlineSH;
	std::vector<gcore::Entity*> healthBarEntities;

	std::vector<PopupText> popupList;

	sf::Font font;

	UserInterface();
	void CreateHealthBar(gcore::Entity* entity);
	void RemoveHealthBar(gcore::Entity* entity);
	void PopupString(const char* text, unsigned int charSize, float time, float xPos, float yPos);
	void PopupNumber(int num, unsigned int charSize, float time, float xPos, float yPos);
	void Render(gcore::Player& player, sf::RenderWindow* window);
};