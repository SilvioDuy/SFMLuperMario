#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"

namespace Game
{
	namespace Core
	{
		//Forward declarations
		class Level;

		/// <summary>
		/// Manages the game flow
		/// </summary>
		class GameManager
		{
		public:
			/// <summary>
			/// Get elapsed time between frames
			/// </summary>
			/// <returns>Delta time beetween frames</returns>
			inline static float getDeltaTime() { return deltaTime; }
			/// <summary>
			/// Get level floor height
			/// </summary>
			/// <returns>Level floor height</returns>
			static float getFloor();
			/// <summary>
			/// Get level gravity force
			/// </summary>
			/// <returns>Level gravity force</returns>
			static float getGravityForce();
			/// <summary>
			/// Get the game window size
			/// </summary>
			/// <returns>Window size in pixels</returns>
			inline static sf::Vector2u getWindowSize() { return gameWindow->getSize(); }
			/// <summary>
			/// Get the original world Y position from an inverted one (with origin at the bottom of the window)
			/// </summary>
			/// <param name="y">Inverted Y</param>
			/// <returns>Original Y position</returns>
			inline static unsigned int getOriginalY(unsigned int y) { return getWindowSize().y - y; }

			/// <summary>
			/// Get all the spawned entities
			/// </summary>
			/// <returns></returns>
			inline static std::vector<WPEntity> getEntities() { return entities; }
			/// <summary>
			/// Remove an entity from the game
			/// </summary>
			/// <param name="entityToRemove">Entity to remove</param>
			static void removeEntity(const Entity* entityToRemove);
			/// <summary>
			/// Adds an entity in the game
			/// </summary>
			/// <param name="entityToAdd">Entity to add</param>
			static void addEntity(WPEntity entityToAdd);

			/// <summary>
			/// Updates all the updatable objects of the game
			/// </summary>
			void updateGame();

			GameManager(sf::RenderWindow* window);
			~GameManager();

		private:
			/// <summary>
			/// Game window
			/// </summary>
			static sf::RenderWindow* gameWindow;
			/// <summary>
			/// Clock that calculates delta time
			/// </summary>
			static sf::Clock gameClock;
			/// <summary>
			/// Delta time between frames
			/// </summary>
			static float deltaTime;

			/// <summary>
			/// Current playing level
			/// </summary>
			static Level* currentLevel;
			/// <summary>
			/// In game spawned entities
			/// </summary>
			static std::vector<WPEntity> entities;
		};
	}
}