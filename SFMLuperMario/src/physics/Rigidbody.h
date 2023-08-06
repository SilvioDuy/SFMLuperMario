#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Game
{
	namespace Physics
	{
		struct Rigidbody
		{
			Rigidbody();

			float mass;
			bool useGravity;
			bool isGrounded;
		};
	}
}