#include "SpriteSheet.h"

namespace gcore
{
	SpriteSheet::SpriteSheet() : widthPerSprite(0), heightPerSprite(0), scale(0)
	{}

	SpriteSheet::SpriteSheet(uint32_t widthPerSprite, uint32_t heightPerSprite, float scale, const char* texturePath)
		: widthPerSprite(widthPerSprite), heightPerSprite(heightPerSprite), scale(scale)
	{
		if (!mainTexture.loadFromFile(texturePath))
			printf("Texture couldn't be found at the given path");
	}

	sf::Sprite SpriteSheet::GetSprite(uint32_t xIndex, uint32_t yIndex)
	{
		int left = xIndex * widthPerSprite;
		int top = yIndex * heightPerSprite;
		sf::IntRect rect(left, top, widthPerSprite, heightPerSprite);
		sf::Sprite sprite(mainTexture, rect);
		sprite.setScale(scale, scale);
		return sprite;
	}
}