#pragma once

#include "Entity.h"

class Player : public Entity
{
	/// <summary>
	/// All the available player animations
	/// </summary>
	enum class PlayerAnimation
	{
		IdleLeft,
		IdleRight,
		MoveLeft,
		MoveRight,
		JumpLeft,
		JumpRight
	};

#pragma region Methods

public:
	virtual void update() override;

	Player(std::string name, sf::Vector2f pos, sf::Vector2f scale, sf::Color col);

private:
	void populateAnimations();
	void jump();

#pragma endregion

#pragma region Attributes

private:
	/// <summary>
	/// Duration of the player jump
	/// </summary>
	const float JUMP_DURATION = 0.5f;
	/// <summary>
	/// Is player jumping
	/// </summary>
	bool isJumping;
	/// <summary>
	/// Speed of the player jump
	/// </summary>
	float jumpSpeed;
	/// <summary>
	/// Current "flying" time since the beginning of jump
	/// </summary>
	float currentJumpTime;
};

#pragma endregion