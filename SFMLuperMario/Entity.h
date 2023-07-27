#pragma once

#include <SFML\Graphics.hpp>
#include "Utils.h"
#include "Animator.h"

/// <summary>
/// Representation of a generic entity of the game
/// </summary>
class Entity
{
#pragma region Methods

public:
	void setTexture(std::string texturePath);

	virtual void update();

	inline sf::Sprite getSprite() { return sprite; }
	inline std::string getName() { return name; }

	Entity(std::string name, sf::Vector2f pos, sf::Vector2f scale, sf::Color col, bool enablePhysics = false);

private:
	void computeGravity();
	void computeCollisions();

#pragma endregion

#pragma region Attributes

public:
	bool isPhysic;
	float movementSpeed;

protected:
	sf::Sprite sprite;
	sf::Texture texture;
	bool isGrounded;

	bool isAnimated;
	Animator animator;

	Orientation currentOrientation;

private:
	const float GRAVITY_FORCE = 240.f;
	std::string name;

#pragma endregion
};