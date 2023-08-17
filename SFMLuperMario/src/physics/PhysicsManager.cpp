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

void PhysicsManager::removeHandler(const PhysicsHandler* handler)
{
	if (handler == nullptr || handlers.begin() >= handlers.end())
		return;

	int index = -1;

	for (unsigned int i = 0; i < handlers.size(); i++)
	{
		if (auto h = handlers[i].lock())
		{
			if (h.get() == handler)
			{
				index = i;
				break;
			}
		}
	}

	if (index < 0)
		return;

	handlers.erase(handlers.begin() + index);
}