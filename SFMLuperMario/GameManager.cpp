#include "GameManager.h"
#include "Entity.h"
#include "Player.h"
#include "Level.h"
#include "Utils.h"

//Static members declaration
sf::RenderWindow* GameManager::gameWindow;
sf::Clock GameManager::gameClock;
float GameManager::deltaTime = 0.f;
std::vector<Entity*> GameManager::entities;
Level* GameManager::currentLevel;

GameManager::GameManager(sf::RenderWindow* window) 
{
	gameWindow = window;
	gameClock.restart();

	currentLevel = new Level();
	currentLevel->loadLevelData(0);

	//addEntity(new Entity("Nemico", sf::Vector2f(500.f, 50.f), sf::Vector2f(1.5f, 1.5f), sf::Color::Blue, true));

	Player* player = new Player("Giocatore", sf::Vector2f(100.f, 50.f), sf::Vector2f(1.f, 1.f), sf::Color::Red);
	addEntity(player);
	player->setTexture("Assets/Sprites/MarioSheet.png");
}

GameManager::~GameManager()
{
	for (int i = entities.size() - 1; i >= 0; i--)
	{
		delete entities[i];
	}

	entities.clear();
	delete currentLevel;
}

void GameManager::updateGame()
{
	deltaTime = gameClock.getElapsedTime().asSeconds();
	gameClock.restart();

	for (Entity* e : entities)
	{
		if (e == nullptr)
			continue;

		e->update();
	}
}

void GameManager::addEntity(Entity* entityToAdd)
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

void GameManager::removeEntity(Entity* entityToRemove)
{
	if (entityToRemove == nullptr)
		return;

	int index = -1;

	for (int i = 0; i < entities.size(); i++)
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
	delete entityToRemove;
}