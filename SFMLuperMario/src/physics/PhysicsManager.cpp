#include <SFML/Graphics.hpp>
#include "PhysicsManager.h"

using namespace Game::Physics;

std::vector<WPPhysicsHandler> PhysicsManager::handlers;

float PhysicsManager::gravityForce = 59.81f;

void PhysicsManager::resolvePhysics()
{
	for (auto const& handler : handlers)
	{
		if (auto h = handler.lock())
		{
			if (!h->enabled)
				continue;

			h->computePhysics(handlers);
		}
	}
}

void PhysicsManager::addHandler(WPPhysicsHandler handler)
{
	handlers.push_back(std::move(handler));
}