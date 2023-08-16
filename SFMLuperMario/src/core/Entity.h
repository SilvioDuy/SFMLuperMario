#pragma once

#include "Component.h"

namespace Game
{
	namespace Core
	{
		/// <summary>
		/// Representation of a generic entity of the game
		/// </summary>
		class Entity : public Component
		{

		public:
			/// <summary>
			/// Horizontal orientation of an entity in the 2D space
			/// </summary>
			enum class HorizontalOrientation
			{
				Left,
				Right
			};

			/// <summary>
			/// Vertical orientation of an entity in the 2D space
			/// </summary>
			enum class VerticalOrientation
			{
				Top,
				Bottom
			};

		public:

			/// <summary>
			/// This method is called every frame
			/// </summary>
			inline virtual void update() {};

			/// <summary>
			/// Current orientation of the entity
			/// </summary>
			HorizontalOrientation currentHorizontalOrientation;
		};

		typedef std::shared_ptr<Entity> PEntity;
		typedef std::weak_ptr<Entity> WPEntity;
	}
}