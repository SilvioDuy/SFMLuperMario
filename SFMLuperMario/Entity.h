#pragma once

#include <SFML\Graphics.hpp>

//Forward declarations
enum class HorizontalOrientation;
class Animator;

/// <summary>
/// Representation of a generic entity of the game
/// </summary>
class Entity
{
#pragma region Methods

public:
	/// <summary>
	/// Loads and sets the sprite's texture
	/// </summary>
	/// <param name="texturePath"></param>
	void setTexture(std::string texturePath);
	/// <summary>
	/// Game update call
	/// </summary>
	virtual void update();
	/// <summary>
	/// Get the entity's sprite
	/// </summary>
	/// <returns>Entity's sprite</returns>
	inline sf::Sprite getSprite() { return sprite; }
	/// <summary>
	/// Get the entity's name
	/// </summary>
	/// <returns>Entity's name</returns>
	inline std::string getName() { return name; }

	Entity(std::string name, sf::Vector2f pos, sf::Vector2f scale, sf::Color col, bool enablePhysics = false);
	~Entity();

private:
	/// <summary>
	/// Computes gravity for this entity
	/// </summary>
	void computeGravity();
	/// <summary>
	/// Computes collisions for this entity
	/// </summary>
	void computeCollisions();

#pragma endregion

#pragma region Attributes

public:
	/// <summary>
	/// Is this entity physic?
	/// </summary>
	bool isPhysic;
	/// <summary>
	/// The movement speed of this entity
	/// </summary>
	float movementSpeed;

protected:
	/// <summary>
	/// The graphics representation of the entity
	/// </summary>
	sf::Sprite sprite;
	/// <summary>
	/// Current texture of the entity
	/// </summary>
	sf::Texture texture;
	/// <summary>
	/// Is this entity grounded?
	/// </summary>
	bool isGrounded;
	/// <summary>
	/// Entity's animator
	/// </summary>
	Animator* animator;
	/// <summary>
	/// Current orientation of the entity
	/// </summary>
	HorizontalOrientation currentOrientation;

private:
	/// <summary>
	/// Entity's name
	/// </summary>
	std::string name;

#pragma endregion
};