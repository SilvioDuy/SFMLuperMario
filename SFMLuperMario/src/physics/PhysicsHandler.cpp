#include "PhysicsHandler.h"
#include "PhysicsManager.h"
#include "../core/GameManager.h"
#include "../core/GameObject.h"
#include "../utils/Utils.h"
#include "../utils/MathUtils.h"

using namespace Game::Physics;

PhysicsHandler::PhysicsHandler(sf::Vector2f pos, bool hasCollider, bool hasRigidbody)
{
	position = new sf::Vector2f(pos);

	if (hasCollider)
	{
		collider = new Collider();
	}

	if (hasRigidbody)
	{
		rigidbody = new Rigidbody();
	}

	onUpdateListeners = new std::vector<OnUpdateDelegate>();
}

PhysicsHandler::~PhysicsHandler()
{
	Game::Core::Component::~Component();

	onUpdateListeners->clear();
	delete onUpdateListeners;

	if (rigidbody)
		delete rigidbody;

	if (collider)
		delete collider;

	delete position;
}

void PhysicsHandler::start()
{
	PhysicsManager::addHandler(gameObject->getComponent<PhysicsHandler>());
}

void PhysicsHandler::addCollider()
{
	if (collider)
	{
		DEBUG_LOG("[Warning] Collider already present");
		return;
	}

	collider = new Collider();
}

void PhysicsHandler::addRigidbody()
{
	if (rigidbody)
	{
		DEBUG_LOG("[Warning] Rigidbody already present");
		return;
	}

	rigidbody = new Rigidbody();
}

void PhysicsHandler::computePhysics(std::vector<WPPhysicsHandler>& handlers)
{
	if (!rigidbody)
		return;

	if (rigidbody->useGravity)
	{
		addForce(PhysicsManager::gravityForce * Game::Core::GameManager::getDeltaTime() * rigidbody->mass, VECTOR_UP);
	}

	if (collider)
	{
		sf::Vector2f collisionOffset(0.f, 0.f);

		for (auto const& handler : handlers)
		{
			if (auto h = handler.lock())
			{
				if (h.get() == this)
					continue;

				collider->checkCollisions(*(h->collider), *position, *h->position);
			}
		}

		*position += collisionOffset;
	}

	gameObject->transform->position = *position;
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
		f(*position);
	}
}

void PhysicsHandler::addForce(float force, sf::Vector2f direction)
{
	*position += direction * force;
}