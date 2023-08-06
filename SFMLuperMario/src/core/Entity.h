#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "../graphics/Animator.h"
#include "../physics/PhysicsHandler.h"

namespace Game
{
	namespace Core
	{
		/// <summary>
		/// Representation of a generic entity of the game
		/// </summary>
		class Entity
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

#pragma region Methods

		public:
			/// <summary>
			/// Loads and sets the sprite's texture
			/// </summary>
			/// <param name="texturePath"></param>
			void setTexture(std::string texturePath, int x, int y, int spriteSize);
			/// <summary>
			/// Adds a Physics Handler to this Entity 
			/// </summary>
			/// <param name="hasCollider">Should add a Collider?</param>
			/// <param name="hasRigidbody">Should add a Rigidbody?</param>
			void addPhysicsHandler(bool hasCollider, bool hasRigidbody);
			/// <summary>
			/// Game update call
			/// </summary>
			virtual void update();
			/// <summary>
			/// Get the entity's sprite
			/// </summary>
			/// <returns>Entity's sprite</returns>
			inline sf::Sprite getSprite() { return sprite; }
			/// <summary>
			/// Get the entity's name
			/// </summary>
			/// <returns>Entity's name</returns>
			inline std::string getName() { return name; }

			Entity(std::string name, sf::Vector2f pos, sf::Vector2f rot, sf::Vector2f scale);
			~Entity();

		protected:
			/// <summary>
			/// Computes gravity for this entity
			/// </summary>
			virtual void onPhysicsUpdate(sf::Vector2f pos);

#pragma endregion

#pragma region Attributes

		public:
			/// <summary>
			/// The movement speed of this entity
			/// </summary>
			float movementSpeed;

		protected:
			/// <summary>
			/// The graphics representation of the entity
			/// </summary>
			sf::Sprite sprite;
			/// <summary>
			/// Current texture of the entity
			/// </summary>
			sf::Texture texture;

			//LEGACY
			/// <summary>
			/// Is this entity grounded?
			/// </summary>
			bool isGrounded;

			/// <summary>
			/// Entity's animator
			/// </summary>
			Game::Graphics::Animator* animator;
			/// <summary>
			/// Current orientation of the entity
			/// </summary>
			HorizontalOrientation currentOrientation;
			/// <summary>
			/// Handles the physics for a game object
			/// </summary>
			Game::Physics::PhysicsHandler* physicsHandler;

		private:
			/// <summary>
			/// Entity's name
			/// </summary>
			std::string name;

#pragma endregion
		};
	}
}