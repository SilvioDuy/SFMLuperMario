#include "Player.h"
#include "GameManager.h"
#include "Animator.h"
#include "Utils.h"

Player::Player(std::string name, sf::Vector2f pos, sf::Vector2f scale, sf::Color col) : Entity(name, pos, scale, col, true)
{
	movementSpeed = 180.f;
	jumpSpeed = 210.f;
	currentJumpTime = 0.f;
	isJumping = false;

	populateAnimations();
}

void Player::populateAnimations()
{
	animator = new Animator(2, 6, 16);

	std::vector<AnimationFrame> frames;
	frames.push_back(AnimationFrame(0, 0, 0));
	animator->addAnimation(Animation(frames, true));

	frames.clear();
	frames.push_back(AnimationFrame(0, 1, 0));
	animator->addAnimation(Animation(frames, true));

	frames.clear();
	frames.push_back(AnimationFrame(1, 0, 0.1f));
	frames.push_back(AnimationFrame(2, 0, 0.1f));
	frames.push_back(AnimationFrame(3, 0, 0.1f));

	animator->addAnimation(Animation(frames, true));

	frames.clear();
	frames.push_back(AnimationFrame(1, 1, 0.1f));
	frames.push_back(AnimationFrame(2, 1, 0.1f));
	frames.push_back(AnimationFrame(3, 1, 0.1f));

	animator->addAnimation(Animation(frames, true));

	frames.clear();
	frames.push_back(AnimationFrame(5, 0, 0));
	animator->addAnimation(Animation(frames, true));

	frames.clear();
	frames.push_back(AnimationFrame(5, 1, 0));
	animator->addAnimation(Animation(frames, true));
}

void Player::update()
{
	Entity::update();

	PlayerAnimation animationToPlay = PlayerAnimation::IdleRight;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
	{
		currentOrientation = HorizontalOrientation::Right;
		sprite.move(movementSpeed * GameManager::getDeltaTime(), 0.f);
		animationToPlay = PlayerAnimation::MoveRight;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		currentOrientation = HorizontalOrientation::Left;
		sprite.move(-movementSpeed * GameManager::getDeltaTime(), 0.f);
		animationToPlay = PlayerAnimation::MoveLeft;
	}
	else
	{
		animationToPlay = currentOrientation == HorizontalOrientation::Left ? PlayerAnimation::IdleLeft : PlayerAnimation::IdleRight;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded) 
	{
		isJumping = true;
	}

	if (isJumping) 
	{
		jump();
		animationToPlay = currentOrientation == HorizontalOrientation::Left ? PlayerAnimation::JumpLeft : PlayerAnimation::JumpRight;
	}

	animator->changeAnimation(static_cast<int>(animationToPlay));
}

void Player::jump()
{
	currentJumpTime += GameManager::getDeltaTime();

	if (currentJumpTime > JUMP_DURATION)
	{
		currentJumpTime = 0.f;
		isGrounded = false;
		isJumping = false;
		return;
	}

	sprite.move(0.f, -jumpSpeed * GameManager::getDeltaTime());
}
