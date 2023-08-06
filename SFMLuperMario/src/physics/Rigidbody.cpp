#include "Rigidbody.h"
#include "PhysicsManager.h"

using namespace Game::Physics;

Rigidbody::Rigidbody()
{
	mass = 1.f;
	useGravity = false;
	isGrounded = false;
}