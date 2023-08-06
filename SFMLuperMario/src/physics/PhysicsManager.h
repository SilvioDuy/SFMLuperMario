#pragma once

#include <iostream>
#include <vector>
#include "PhysicsHandler.h"

namespace Game
{
	namespace Physics
	{
		class PhysicsManager
		{		

		public:
			void update();

			static void addHandler(PhysicsHandler* handler);

		public:
			static float gravityForce;

		private:
			static std::vector<PPhysicsHandler> handlers;
		};
	}
}

