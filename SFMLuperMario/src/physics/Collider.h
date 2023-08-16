#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace Game
{
	namespace Physics
	{
		struct Collider
		{
			sf::Vector2f size;
			bool isTrigger;

			Collider();
			sf::Vector2f checkCollisions(Collider other, sf::Vector2f pos, sf::Vector2f otherPos);
		};
	}
}