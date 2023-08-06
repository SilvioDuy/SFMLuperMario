#include <SFML/Graphics.hpp>
#include "PhysicsManager.h"

using namespace Game::Physics;

std::vector<PPhysicsHandler> PhysicsManager::handlers;

float PhysicsManager::gravityForce = 9.81f;

void PhysicsManager::update()
{
	for (auto const& h : handlers)
	{
		h->computePhysics(handlers);
	}
}

void PhysicsManager::addHandler(PhysicsHandler* handler)
{
	handlers.push_back(std::make_shared<PhysicsHandler>(*handler));
}