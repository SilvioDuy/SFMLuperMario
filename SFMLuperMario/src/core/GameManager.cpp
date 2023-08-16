#include "GameManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Level.h"
#include "../utils/Utils.h"

using namespace Game::Core;

//Static members declaration
Level* GameManager::currentLevel;
std::vector<WPEntity> GameManager::entities;

sf::RenderWindow* GameManager::gameWindow;

sf::Clock GameManager::gameClock;
float GameManager::deltaTime = 0.f;

GameManager::GameManager(sf::RenderWindow* window) 
{
	gameWindow = window;
	gameClock.restart();

	currentLevel = new Level();
	currentLevel->loadLevelData(0);

	GameObject* playerGO = new GameObject("Player");
	PPlayer player = playerGO->addComponent<Player>();
	addEntity(player);
}

GameManager::~GameManager()
{
	entities.clear();
	delete currentLevel;
}

void GameManager::updateGame()
{
	deltaTime = gameClock.getElapsedTime().asSeconds();
	gameClock.restart();

	for (auto const& entity : entities)
	{
		if (auto e = entity.lock())
		{
			if (!e->enabled)
				continue;

			e->update();
		}
	}
}

void GameManager::addEntity(WPEntity entityToAdd)
{
	entities.push_back(std::move(entityToAdd));
}

float GameManager::getFloor()
{
	return currentLevel->getFloorHeight();
}

float GameManager::getGravityForce()
{
	return currentLevel->getGravityForce();
}

void GameManager::removeEntity(const Entity* entityToRemove)
{
	if (entityToRemove == nullptr || entities.begin() >= entities.end())
		return;

	int index = -1;

	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (auto e = entities[i].lock())
		{
			if (e.get() == entityToRemove)
			{
				index = i;
				break;
			}
		}
	}

	if (index < 0)
		return;

	entities.erase(entities.begin() + index);
}