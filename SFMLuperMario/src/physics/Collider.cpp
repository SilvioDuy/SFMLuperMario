#include "Collider.h"
#include "PhysicsManager.h"
#include "../utils/Utils.h"

using namespace Game::Physics;

Collider::Collider()
{
	isTrigger = false;
	size = sf::Vector2f(0.f, 0.f);
}

sf::Vector2f Collider::checkCollisions(Collider other, sf::Vector2f pos, sf::Vector2f otherPos)
{
	sf::Vector2f offset(0.f, 0.f);

	float minDistanceX = size.x * 0.5f + other.size.x * 0.5f;
	float minDistanceY = size.y * 0.5f + other.size.y * 0.5f;

	float x = pos.x - otherPos.x;
	float xAbs = abs(x);
	float y = pos.y - otherPos.y;
	float yAbs = abs(y);

	if (xAbs < minDistanceX && yAbs < minDistanceY)
	{
		float xDiff = minDistanceX - xAbs;
		float yDiff = minDistanceY - yAbs;
		if (xDiff < yDiff)
			offset.x = (minDistanceX - xAbs) * (x / xAbs);
		else
			offset.y = (minDistanceY - yAbs) * (y / yAbs);
	}

	return offset;
}