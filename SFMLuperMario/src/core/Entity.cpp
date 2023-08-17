#include "Entity.h"
#include "GameManager.h"

using namespace Game::Core;

void Entity::onDestroy()
{
	GameManager::removeEntity(this);
};