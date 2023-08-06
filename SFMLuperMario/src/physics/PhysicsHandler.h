#pragma once

#include <functional>
#include <vector>
#include "Rigidbody.h"
#include "Collider.h"

#define PPhysicsHandler std::shared_ptr<PhysicsHandler>
#define OnUpdateDelegate std::function<void(sf::Vector2f)>

namespace Game
{
	namespace Physics
	{
		class PhysicsHandler
		{
		public:
			void addCollider();
			void addRigidbody();

			void addForce(float force, sf::Vector2f direction);
			void computePhysics(std::vector<PPhysicsHandler>& handlers);
			void subscribeToUpdate(OnUpdateDelegate callback);

			PhysicsHandler(sf::Vector2f pos, bool hasCollider = false, bool hasRigidbody = false);
			~PhysicsHandler();

		private:
			void invokeOnUpdate();

		public:
			Rigidbody* rigidbody;
			Collider* collider;

		private:
			std::vector<OnUpdateDelegate>* onUpdateListeners;
			sf::Vector2f position;
		};
	}
}