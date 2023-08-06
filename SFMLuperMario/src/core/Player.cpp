#include <functional>
#include "Player.h"
#include "GameManager.h"
#include "../graphics/Animator.h"
#include "../graphics/Animation.h"
#include "../utils/Utils.h"
#include "../utils/MathUtils.h"

using namespace Game::Core;

Player::Player(std::string name, sf::Vector2f pos, sf::Vector2f rot, sf::Vector2f scale) : Entity(name, pos, rot, scale)
{
	movementSpeed = 180.f;
	jumpSpeed = 210.f;
	currentJumpTime = 0.f;
	isJumping = false;

	addPhysicsHandler(true, true);

	populateAnimations();
}

void Player::populateAnimations()
{
	animator = new Game::Graphics::Animator(2, 7, (int)PLAYER_SPRITE_SIZE);

	for (int i = PlayerAnimation::Idle; i <= PlayerAnimation::Jump; ++i)
	{
		std::string s(playerAnimToString[i]);
		animator->addAnimation(Game::Graphics::Animation::loadAnimation("Mario/" + s));
	}

	/*frames.clear();
	frames.push_back(AnimationFrame(0, 1, 0));
	animator->addAnimation(Animation(frames, true));*/

	/*frames.clear();
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
	animator->addAnimation(Animation(frames, true));*/
}

void Player::update()
{
	Entity::update();

	PlayerAnimation animationToPlay = PlayerAnimation::Idle;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
	{
		currentOrientation = HorizontalOrientation::Right;
		physicsHandler->addForce(movementSpeed * GameManager::getDeltaTime(), VECTOR_RIGHT);
		//sprite.move(movementSpeed * GameManager::getDeltaTime(), 0.f);
		animationToPlay = PlayerAnimation::Move;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		currentOrientation = HorizontalOrientation::Left;
		physicsHandler->addForce(movementSpeed * GameManager::getDeltaTime(), VECTOR_LEFT);

		//sprite.move(-movementSpeed * GameManager::getDeltaTime(), 0.f);
		animationToPlay = PlayerAnimation::Move;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded) 
	{
		isJumping = true;
	}

	if (isJumping) 
	{
		jump();
		animationToPlay = PlayerAnimation::Jump;
	}

	if (currentOrientation == HorizontalOrientation::Left)
	{
		sprite.setScale(sf::Vector2f(-1, 1));
	}
	else
	{
		sprite.setScale(sf::Vector2f(1, 1));
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

	physicsHandler->addForce(jumpSpeed * GameManager::getDeltaTime(), VECTOR_UP);
	//sprite.move(0.f, -jumpSpeed * GameManager::getDeltaTime());
}
