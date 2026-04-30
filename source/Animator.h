#pragma once
#include "SpriteSheet.h"
#include <map>

namespace gcore
{
	class Animation
	{
	public:
		const char* name;
		SpriteSheet spriteSheet;
		bool isSheetHorizontal;
		int spriteCount;
		float frameLength;
		bool onLoop;

		Animation();
		Animation(const char* name, const SpriteSheet& spriteSheet, bool isSheetHorizontal, int spCount, float frameLength, bool onLoop);

		sf::Sprite GetSprite(uint32_t index);
	};

	class Animator
	{
	private:
		sf::Sprite currentSprite;
		Animation* currentAnimation;
		std::map<const char*, Animation> animations;
		int currentFrameIndex;
		float timer;
	public:
		bool stop;

		Animator();

		void Tick(float deltaTime);
		void Play(const char* animationName);
		void AddAnimation(Animation anim);
		sf::Sprite& GetCurrentSprite();
	};
}