#pragma once

#include "SFML/Graphics.hpp"

namespace gcore
{
	class SpriteSheet
	{
	public:
		sf::Texture mainTexture;
		const uint32_t widthPerSprite;
		const uint32_t heightPerSprite;
		const float scale;

		SpriteSheet();
		SpriteSheet(uint32_t widthPerSprite, uint32_t heightPerSprite, float scale, const char* texturePath);

		sf::Sprite GetSprite(uint32_t xIndex, uint32_t yIndex);
	};
}