#include "Collider.h"
#include "PhysicsManager.h"

using namespace Game::Physics;

Collider::Collider()
{
	
}

sf::Vector2f Collider::checkCollisions(Collider other, sf::Vector2f pos, sf::Vector2f otherPos)
{
	sf::Vector2f offset(0.f, 0.f);

	float minDistanceX = size.x * 0.5f + other.size.x * 0.5f;
	float minDistanceY = size.y * 0.5f + other.size.y * 0.5f;

	//if (abs(position.x - other.position.x) > minDistanceX || abs(position.y - other.position.y) > minDistanceY)

	offset.x = std::min(0.f, minDistanceX - abs(pos.x - otherPos.x));
	offset.y = std::min(0.f, minDistanceY - abs(pos.y - otherPos.y));

	/*if (sprite.getPosition().y + halfShapeSize >= GameManager::getFloor())
	{
		isGrounded = true;
		sprite.setPosition(sf::Vector2f(sprite.getPosition().x, GameManager::getFloor() - halfShapeSize));
	}*/

	return offset;
}