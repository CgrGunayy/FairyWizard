#include "Animator.h"

namespace gcore
{
	Animator::Animator() : currentSprite(sf::Sprite()), currentAnimation(nullptr), currentFrameIndex(-1), timer(0), stop(false)
	{}

	Animation::Animation() : name("null"), spriteSheet(SpriteSheet()), isSheetHorizontal(true), spriteCount(0), frameLength(0), onLoop(false)
	{}

	Animation::Animation(const char* name, const SpriteSheet& spriteSheet, bool isSheetHorizontal, int spCount, float frameLength, bool onLoop)
		: name(name), spriteSheet(spriteSheet), isSheetHorizontal(isSheetHorizontal), spriteCount(spCount), frameLength(frameLength), onLoop(onLoop)
	{}

	sf::Sprite Animation::GetSprite(uint32_t index)
	{
		if (isSheetHorizontal)
			return spriteSheet.GetSprite(index, 0);
		else
			return spriteSheet.GetSprite(0, index);
	}

	void Animator::Tick(float deltaTime)
	{
		if (stop)
			return;

		if (currentAnimation == nullptr)
		{
			timer = 0;
			return;
		}

		if (timer < currentAnimation->frameLength)
			timer += deltaTime;
		else
		{
			timer = 0;
			currentFrameIndex += 1;
			if (currentFrameIndex >= currentAnimation->spriteCount)
			{
				if (currentAnimation->onLoop)
				{
					currentFrameIndex = 0;
					currentSprite = currentAnimation->GetSprite(currentFrameIndex);
				}
				else
				{
					currentFrameIndex = -1;
					currentAnimation = nullptr;
				}
			}
			else
			{
				currentSprite = currentAnimation->GetSprite(currentFrameIndex);
			}
		}
	}
	void Animator::Play(const char* animationName)
	{
		currentAnimation = &(animations[animationName]);
		currentFrameIndex = 0;
		timer = 0;
		currentSprite = currentAnimation->GetSprite(currentFrameIndex);
	}
	void Animator::AddAnimation(Animation anim)
	{
		animations.insert(std::pair<const char*, Animation>(anim.name, anim));
	}
	sf::Sprite& Animator::GetCurrentSprite()
	{
		return currentSprite;
	}
}