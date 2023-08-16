#pragma once

#include <SFML/Graphics.hpp>

namespace Game
{
	namespace Core
	{
		struct Transform
		{
			sf::Vector2f position;
			sf::Vector2f scale;
			float rotation;

			inline Transform() : position(sf::Vector2f(0.f, 0.f)), scale(sf::Vector2f(1.f, 1.f)), rotation(0.f) {};
			inline virtual ~Transform() {};
		};
	}
}