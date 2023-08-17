#include <string>
#include <functional>
#include "Player.h"
#include "GameManager.h"
#include "GameObject.h"
#include "../graphics/Renderer.h"
#include "../graphics/Animator.h"
#include "../utils/Utils.h"
#include "../utils/MathUtils.h"
#include "../utils/AssetsUtils.h"

using namespace Game::Core;

void Player::start()
{
	movementSpeed = 180.f;
	jumpSpeed = 210.f;
	currentJumpTime = 0.f;
	isJumping = false;
	currentHorizontalOrientation = Entity::HorizontalOrientation::Right;

	auto physicsHandler = new Game::Physics::PhysicsHandler(gameObject->transform->position, true, true);
	physicsHandler->rigidbody->useGravity = true;
	physicsHandler->collider->size = sf::Vector2f(16.f, 16.f);

	gameObject->addComponent<Game::Physics::PhysicsHandler>(physicsHandler);
	std::weak_ptr<Game::Graphics::Renderer> renderer = gameObject->addComponent<Game::Graphics::Renderer>();

	std::string textureName = "MarioSheet";

	if (auto r = renderer.lock())
		r->setTexture(SPRITES_DIR + textureName + PNG_EXTENSION, 0, 0, 16, 16);

	populateAnimations();

	gameObject->transform->position = sf::Vector2f(100.f, 50.f);
}

void Player::populateAnimations()
{
	Game::Graphics::Animator* animator = new Game::Graphics::Animator(2, 7, (int)PLAYER_SPRITE_SIZE);

	for (int i = PlayerAnimation::Idle; i <= PlayerAnimation::Jump; ++i)
	{
		std::string s(playerAnimToString[i]);
		animator->addAnimation(Game::Graphics::Animation::loadAnimation("Mario/" + s));
	}

	gameObject->addComponent<Game::Graphics::Animator>(animator);
}

void Player::update()
{
	PlayerAnimation animationToPlay = PlayerAnimation::Idle;
	HorizontalOrientation newOrientation = currentHorizontalOrientation;
	auto physicsHandler = gameObject->getComponent<Game::Physics::PhysicsHandler>();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
	{
		newOrientation = HorizontalOrientation::Right;
		physicsHandler->addForce(movementSpeed * GameManager::getDeltaTime(), VECTOR_RIGHT);
		animationToPlay = PlayerAnimation::Move;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		newOrientation = HorizontalOrientation::Left;
		physicsHandler->addForce(movementSpeed * GameManager::getDeltaTime(), VECTOR_LEFT);
		animationToPlay = PlayerAnimation::Move;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
	{
		isJumping = true;
	}

	if (isJumping) 
	{
		jump(physicsHandler);
		animationToPlay = PlayerAnimation::Jump;
	}

	if (currentHorizontalOrientation != newOrientation)
	{
		gameObject->transform->scale.x *= -1;
		currentHorizontalOrientation = newOrientation;
	}

	gameObject->getComponent<Game::Graphics::Animator>()->changeAnimation(static_cast<int>(animationToPlay));
}

void Player::jump(Game::Physics::PPhysicsHandler physicsHandler)
{
	currentJumpTime += GameManager::getDeltaTime();

	if (currentJumpTime > JUMP_DURATION)
	{
		currentJumpTime = 0.f;
		//isGrounded = false;
		isJumping = false;
		return;
	}

	physicsHandler->addForce(jumpSpeed * GameManager::getDeltaTime(), VECTOR_DOWN);
}
