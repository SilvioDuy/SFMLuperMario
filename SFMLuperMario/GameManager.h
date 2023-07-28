#pragma once

#include <SFML\Graphics.hpp>

//Forward declarations
class Level;
class Entity;

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
	/// Get all the spawned entities
	/// </summary>
	/// <returns></returns>
	inline static std::vector<Entity*> getEntities() { return entities; }
	/// <summary>
	/// Remove an entity from the game
	/// </summary>
	/// <param name="entityToRemove">Entity to remove</param>
	static void removeEntity(Entity* entityToRemove);
	/// <summary>
	/// Add an entity in the game
	/// </summary>
	/// <param name="entityToAdd">Entity to add</param>
	static void addEntity(Entity* entityToAdd);

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
	static std::vector<Entity*> entities;
};

