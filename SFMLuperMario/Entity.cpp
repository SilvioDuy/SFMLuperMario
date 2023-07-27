#include "Entity.h"
#include "GameManager.h"

#include <iostream>

using namespace sf;

Entity::Entity(std::string entityName, Vector2f pos, Vector2f scale, Color col, bool enablePhysics) 
{
	name = entityName;
	isPhysic = enablePhysics;

	sprite.setOrigin(scale * 0.5f);
	sprite.setPosition(pos);
	sprite.setScale(scale);

	movementSpeed = 5.f;
	isAnimated = false;

	currentOrientation = Orientation::Right;
}

void Entity::update()
{
	if (isAnimated)
	{
		animator.animateSprite(sprite);
	}

	if (isPhysic)
	{
		computeGravity();
		computeCollisions();
	}
}

void Entity::computeGravity() 
{
	if (isGrounded)
		return;

	sprite.move(0.f, GRAVITY_FORCE * GameManager::getDeltaTime());

	float halfShapeSize = sprite.getScale().y * 0.5f;

	if (sprite.getPosition().y + halfShapeSize >= GameManager::getFloor())
	{
		isGrounded = true;
		sprite.setPosition(Vector2f(sprite.getPosition().x, GameManager::getFloor() - halfShapeSize));
	}
}

void Entity::computeCollisions() 
{
	//TODO: Adapt collisions to sprite system
	/*for (Entity* e : GameManager::getEntities())
	{
		if (e == nullptr || e == this || !e->isPhysic)
			continue;

		Sprite entityShape = e->getSprite();
		float minDistanceX = entityShape.getSize().x * 0.5f + sprite->getScale().x * 0.5f;
		float minDistanceY = entityShape.getSize().y * 0.5f + sprite->getScale().y * 0.5f;

		if (abs(entityShape.getPosition().x - sprite->getPosition().x) > minDistanceX ||
			abs(entityShape.getPosition().y - sprite->getPosition().y) > minDistanceY)
			continue;

		std::cout << this->getName() << " collided with: " << e->name << std::endl;
	}*/
}

void Entity::setTexture(std::string texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		log("Didn't find texture: " << texturePath << " for entity " << name);
		return;
	}

	sprite.setTexture(texture);
}