#include "Animator.h"
#include "GameManager.h"

Animator::Animator(int rows, int cols, int size)
{
	sheetRows = rows;
	sheetCols = cols;
	spriteSize = size;
	currentAnimationId = 0;
	currentFrame = 0;
	currentFrameT = 0;
}

Animator::~Animator()
{
	animations.clear();
}

void Animator::animateSprite(sf::Sprite& spr)
{
	Animation currentAnim = animations[currentAnimationId];
	
	int x = spriteSize * currentAnim.frames[currentFrame].xPos;
	int y = spriteSize * currentAnim.frames[currentFrame].yPos;

	spr.setTextureRect(sf::IntRect(x, y, spriteSize, spriteSize));

	int framesCount = currentAnim.frames.size();

	if (framesCount > 1)
	{
		currentFrameT += GameManager::getDeltaTime();

		if (currentFrameT < currentAnim.frames[currentFrame].duration)
			return;

		currentFrame++;
		currentFrameT = 0;

		if (currentAnim.loop)
		{
			currentFrame %= framesCount;
		}
		else if (currentFrame >= framesCount)
		{
			currentFrame = framesCount - 1;
		}
	}
}

void Animator::changeAnimation(int animationId)
{
	if (currentAnimationId == animationId)
		return;

	currentAnimationId = animationId;
	currentFrame = 0;
}

void Animator::addAnimation(Animation anim)
{
	animations.push_back(anim);
}