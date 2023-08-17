#include "GameObject.h"
#include "Component.h"
#include "../utils/Utils.h"

using namespace Game::Core;

void GameObject::destroy()
{
	if (isDestroyed)
		return;

	isDestroyed = true;

	for (auto c : components)
	{
		c.second->onDestroy();
	}

	components.clear();

	delete this;
}

GameObject* GameObject::instantiate(const std::string name)
{
	return new GameObject(name);
}