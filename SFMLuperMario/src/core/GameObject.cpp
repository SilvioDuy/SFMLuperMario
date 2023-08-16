#include "GameObject.h"
#include "Component.h"
#include "../utils/Utils.h"

using namespace Game::Core;

GameObject::~GameObject()
{
	components.clear();
}