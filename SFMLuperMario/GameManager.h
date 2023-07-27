#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Utils.h"

class GameManager
{
public:
	inline static float getDeltaTime() { return deltaTime; }

	inline static float getFloor() { return floor; }

	inline static std::vector<Entity*> getEntities() { return entities; }
	static void removeEntity(Entity* entityToRemove);
	static void addEntity(Entity* entityToAdd);

	void updateGame();

	GameManager(sf::RenderWindow& window);
	~GameManager();

private:
	static sf::Clock gameClock;
	static float deltaTime;
	static float floor;
	static std::vector<Entity*> entities;
	float floorHeight = 80.f;
};

