#include "GameManager.h"
#include "Entity.h"
#include "Player.h"
#include "Level.h"
#include "../utils/Utils.h"

using namespace Game::Core;

//Static members declaration
Level* GameManager::currentLevel;
std::vector<PEntity> GameManager::entities;

sf::RenderWindow* GameManager::gameWindow;

sf::Clock GameManager::gameClock;
float GameManager::deltaTime = 0.f;

GameManager::GameManager(sf::RenderWindow* window) 
{
	gameWindow = window;
	gameClock.restart();

	physicsManager = new Game::Physics::PhysicsManager();

	currentLevel = new Level();
	currentLevel->loadLevelData(0);

	std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player("Giocatore", sf::Vector2f(100.f, 50.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f)));
	player->setTexture("Assets/Sprites/MarioSheet.png", 0, 0, (int)PLAYER_SPRITE_SIZE);
	addEntity(std::move(player));
}

GameManager::~GameManager()
{
	entities.clear();
	delete currentLevel;
	delete physicsManager;
}

void GameManager::updateGame()
{
	if (physicsManager)
	{
		physicsManager->update();
	}

	deltaTime = gameClock.getElapsedTime().asSeconds();
	gameClock.restart();

	for (auto const& e : entities)
	{
		if (e == nullptr)
			continue;

		e->update();
	}
}

void GameManager::addEntity(PEntity entityToAdd)
{
	entities.push_back(entityToAdd);
}

float GameManager::getFloor()
{
	return currentLevel->getFloorHeight();
}

float GameManager::getGravityForce()
{
	return currentLevel->getGravityForce();
}

void GameManager::removeEntity(PEntity entityToRemove)
{
	if (entityToRemove == nullptr)
		return;

	int index = -1;

	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities[i] == entityToRemove)
		{
			index = i;
			break;
		}
	}

	if (index < 0)
		return;

	entities.erase(entities.begin() + index);
}