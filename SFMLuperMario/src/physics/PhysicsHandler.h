#pragma once

#include <functional>
#include <vector>
#include "Rigidbody.h"
#include "Collider.h"
#include "../core/Component.h"

namespace Game
{
	namespace Physics
	{
		typedef std::function<void(sf::Vector2f)> OnUpdateDelegate;

		class PhysicsHandler : public Game::Core::Component
		{
		public:
			void addCollider();
			void addRigidbody();

			void addForce(float force, sf::Vector2f direction);
			void computePhysics(std::vector<std::weak_ptr<PhysicsHandler>>& handlers);
			void subscribeToUpdate(OnUpdateDelegate callback);

			virtual void start() override;
			void update() {};

			inline PhysicsHandler() : position(new sf::Vector2f(0.f, 0.f)), rigidbody(nullptr), collider(nullptr), onUpdateListeners(new std::vector<OnUpdateDelegate>) {};
			PhysicsHandler(sf::Vector2f pos, bool hasCollider = false, bool hasRigidbody = false);
			~PhysicsHandler();

		private:
			void invokeOnUpdate();

		public:
			Rigidbody* rigidbody;
			Collider* collider;

		private:
			std::vector<OnUpdateDelegate>* onUpdateListeners;
			sf::Vector2f* position;
		};

		typedef std::shared_ptr<PhysicsHandler> PPhysicsHandler;
		typedef std::weak_ptr<PhysicsHandler> WPPhysicsHandler;
	}
}