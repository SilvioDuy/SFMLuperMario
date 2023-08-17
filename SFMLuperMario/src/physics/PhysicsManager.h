#pragma once

#include <iostream>
#include "PhysicsHandler.h"

namespace Game
{
	namespace Physics
	{
		class PhysicsManager
		{		

		public:
			void resolvePhysics();

			static void addHandler(WPPhysicsHandler handler);
			static void removeHandler(const PhysicsHandler* handler);

		public:
			static float gravityForce;

		private:
			static std::vector<WPPhysicsHandler> handlers;
		};
	}
}

