#include "PhysicsHandler.h"
#include "PhysicsManager.h"
#include "../core/GameManager.h"
#include "../utils/Utils.h"
#include "../utils/MathUtils.h"

using namespace Game::Physics;

PhysicsHandler::PhysicsHandler(sf::Vector2f pos, bool hasCollider, bool hasRigidbody)
{
	position = pos;

	if (hasCollider)
	{
		collider = new Collider();
	}

	if (hasRigidbody)
	{
		rigidbody = new Rigidbody();
	}

	onUpdateListeners = new std::vector<OnUpdateDelegate>();
	PhysicsManager::addHandler(this);
}

PhysicsHandler::~PhysicsHandler()
{
	onUpdateListeners->clear();
	delete onUpdateListeners;

	if (rigidbody)
		delete rigidbody;

	if (collider)
		delete collider;
}


void PhysicsHandler::addCollider()
{
	if (collider)
	{
		log("[Warning] Collider already present");
		return;
	}

	collider = new Collider();
}

void PhysicsHandler::addRigidbody()
{
	if (rigidbody)
	{
		log("[Warning] Rigidbody already present");
		return;
	}

	rigidbody = new Rigidbody();
}

void PhysicsHandler::computePhysics(std::vector<PPhysicsHandler>& handlers)
{
	if (!rigidbody)
		return;

	if (rigidbody->useGravity)
	{
		addForce(PhysicsManager::gravityForce * Game::Core::GameManager::getDeltaTime() * rigidbody->mass, VECTOR_DOWN);
	}

	if (collider)
	{
		sf::Vector2f collisionOffset(0.f, 0.f);

		for (auto const& h : handlers)
		{
			if (h.get() == this)
				continue;

			collider->checkCollisions(*(h->collider), position, h->position);
		}

		position += collisionOffset;
	}

	invokeOnUpdate();
}

void PhysicsHandler::subscribeToUpdate(OnUpdateDelegate callback)
{
	onUpdateListeners->push_back(callback);
}

void PhysicsHandler::invokeOnUpdate()
{
	for (auto const& f : *onUpdateListeners)
	{
		f(position);
	}
}

void PhysicsHandler::addForce(float force, sf::Vector2f direction)
{
	position += direction * force;
}