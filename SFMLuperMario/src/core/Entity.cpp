#include <iostream>
#include "Entity.h"
#include "GameManager.h"
#include "../utils/Utils.h"
#include "../physics/Rigidbody.h"

using namespace Game::Core;

Entity::Entity(std::string entityName, sf::Vector2f pos, sf::Vector2f rot, sf::Vector2f scale) 
{
	name = entityName;

	sprite.setScale(scale);
	sprite.setPosition(pos);

	movementSpeed = 5.f;

	currentOrientation = HorizontalOrientation::Right;
}

Entity::~Entity()
{
	delete animator;
}

void Entity::update()
{
	if (animator)
	{
		animator->animateSprite(sprite);
	}
}

void Entity::addPhysicsHandler(bool hasCollider, bool hasRigidbody)
{
	if (physicsHandler)
	{
		log("[Warning] Physics Handler already present on" << name);
		return;
	}

	physicsHandler = new Game::Physics::PhysicsHandler(sprite.getPosition(), hasCollider, hasRigidbody);
	physicsHandler->subscribeToUpdate([&](sf::Vector2f pos) { return this->onPhysicsUpdate(pos); });
}

void Entity::onPhysicsUpdate(sf::Vector2f pos) 
{
	sprite.setPosition(pos);
}

void Entity::setTexture(std::string texturePath, int x, int y, int spriteSize)
{
	if (!texture.loadFromFile(texturePath))
	{
		log("Didn't find texture: " << texturePath << " for entity " << name);
		return;
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(x, y, spriteSize, spriteSize));
	sprite.setOrigin(sprite.getScale() * (float)spriteSize * 0.5f);
}