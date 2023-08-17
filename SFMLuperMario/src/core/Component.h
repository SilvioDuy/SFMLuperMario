#pragma once

#include <memory>

namespace Game 
{
	namespace Core
	{
		class GameObject;

		struct Component 
		{
			GameObject* gameObject;
			bool enabled;

			inline Component() : enabled(false) {};
			inline virtual void start() {};
			inline virtual void onDestroy() {};
		};

		typedef std::shared_ptr<Component> PComponent;
	}
}

