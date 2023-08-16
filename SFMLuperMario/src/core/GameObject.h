#pragma once

#include <iostream>
#include <map>
#include <typeinfo>
#include <typeindex>
#include "Component.h"
#include "Transform.h"
#include "../utils/Utils.h"

namespace Game
{
	namespace Core
	{
		class GameObject
		{
		public:
			/// <summary>
			/// Gets a component from this Game Object
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <returns></returns>
			template <typename T>
			std::shared_ptr<T> getComponent()
			{
				auto component = components.find(typeid(T));

				if (component != components.end())
					return std::dynamic_pointer_cast<T>(component->second);
			
				return nullptr;
			}

			/// <summary>
			/// Adds a component to this Game Object
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <param name="componentToAdd"></param>
			/// <returns></returns>
			template <typename T>
			std::shared_ptr<T> addComponent(T* componentToAdd = nullptr)
			{
				std::type_index newComponentType = typeid(T);

				if (newComponentType == typeid(Component))
				{
					DEBUG_LOG("Can't add an 'base' Component to GameObject " << name);
					return nullptr;
				}

				T* newComponent = componentToAdd == nullptr ? new T() : componentToAdd;
				Component* c = dynamic_cast<Component*>(newComponent);

				if (c == nullptr)
				{
					DEBUG_LOG("Can't add a non-Component class to GameObject " << name);
					delete newComponent;
					return nullptr;
				}

				std::shared_ptr<T> existingComponent = getComponent<T>();
				if (existingComponent != nullptr)
				{
					DEBUG_LOG("GameObject " << name << " already contains a component of type " << newComponentType.name());
					return existingComponent;
				}

				c->gameObject = this;
				c->enabled = true;

				std::pair<std::type_index, std::shared_ptr<T>> myPair(typeid(T), std::shared_ptr<T>(newComponent));

				components.insert(myPair);

				c->start();

				return myPair.second;
			}

			inline GameObject() : name("GameObject"), transform(std::shared_ptr<Transform>(new Transform())) {};
			inline GameObject(std::string gameObjectName) : name(gameObjectName), transform(std::shared_ptr<Transform>(new Transform())) {};
			~GameObject();

		public:
			std::string name;
			std::shared_ptr<Transform> transform;

		private:
			std::map<std::type_index, PComponent> components;
		};
	}
}