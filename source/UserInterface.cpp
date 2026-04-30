#include "UserInterface.h"

extern sf::RenderWindow* window;

UserInterface::UserInterface() 
	: wandSH(80, 16, 3, "vendor/wand.png"),
	  wandOutlineSH(80, 16, 3, "vendor/wand_outline.png"),
	  healthbarFillSH(16, 16, 5, "vendor/healthbar_fill.png"),
	  healthbarOutlineSH(16, 16, 5, "vendor/healthbar_outline.png")	  
{
	if(!font.loadFromFile("vendor/alagard.ttf"))
		printf("Font couldn't be found");
}

void UserInterface::CreateHealthBar(gcore::Entity* entity)
{
	healthBarEntities.push_back(entity);
}

void UserInterface::RemoveHealthBar(gcore::Entity* entity)
{
	healthBarEntities.erase(std::remove(healthBarEntities.begin(), healthBarEntities.end(), entity), healthBarEntities.end());
}

void UserInterface::PopupString(const char* text, unsigned int charSize, float time, float xPos, float yPos)
{
	sf::Text txt;
	txt.setFont(font);
	txt.setString(text);
	txt.setCharacterSize(charSize);
	txt.setFillColor(sf::Color::White);
	txt.setPosition(xPos, yPos);

	PopupText popup(txt, time);
	popupList.push_back(popup);
}

void UserInterface::PopupNumber(int num, unsigned int charSize, float time, float xPos, float yPos)
{
	sf::Text txt;
	txt.setFont(font);

	std::string t = std::to_string(num);
	char const* n_char = t.c_str();

	txt.setString(n_char);
	txt.setCharacterSize(charSize);
	txt.setFillColor(sf::Color::White);
	txt.setPosition(xPos, yPos);

	PopupText popup(txt, time);
	popupList.push_back(popup);
}

void UserInterface::Render(gcore::Player& player, sf::RenderWindow* window)
{
	for (auto ent : healthBarEntities)
	{
		float hp = ent->currentHealth / (float)ent->maxHealth;

		sf::Sprite healthSP = healthbarFillSH.GetSprite(0, 0);
		sf::Sprite healthOutSP = healthbarOutlineSH.GetSprite(0, 0);

		healthSP.setTextureRect(sf::IntRect(0, 0, round(16 * hp), 16));

		healthSP.setPosition(ent->xPos + ent->hpbarOffsetX, ent->yPos + ent->hpbarOffsetY);
		healthOutSP.setPosition(ent->xPos + ent->hpbarOffsetX, ent->yPos + ent->hpbarOffsetY);

		window->draw(healthSP);
		window->draw(healthOutSP);
	}

	for (auto& popup : popupList)
	{
		if (popup.timer > 0)
		{
			window->draw(popup.text);
		}
	}

	float healthPercent = player.currentHealth / (float)player.maxHealth;

	sf::Sprite wandSp = wandSH.GetSprite(0, 0);
	sf::Sprite wandOutSP = wandOutlineSH.GetSprite(0, 0);

	wandSp.setTextureRect(sf::IntRect(0, 0, round(80 * healthPercent), 16));

	wandSp.setPosition(8, 16);
	wandOutSP.setPosition(8, 16);

	window->draw(wandSp);
	window->draw(wandOutSP);
}