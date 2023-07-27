#pragma once

#include "Entity.h"

class Player : public Entity
{
	enum class PlayerAnimation
	{
		IdleLeft,
		IdleRight,
		MoveLeft,
		MoveRight,
		JumpLeft,
		JumpRight
	};

public:
	void update();

	Player(std::string name, sf::Vector2f pos, sf::Vector2f scale, sf::Color col);

private:
	const float JUMP_DURATION = 0.5f;

	bool isJumping;
	float jumpSpeed;
	float currentJumpTime;

	void jump();
};

