#include "GameManager.h"

sf::Clock GameManager::gameClock;
float GameManager::deltaTime = 0.f;
float GameManager::floor = 0.f;
std::vector<Entity*> GameManager::entities;

GameManager::GameManager(sf::RenderWindow& window) 
{
	floor = window.getSize().y - floorHeight;
	gameClock.restart();
	addEntity(new Entity("Nemico", sf::Vector2f(500.f, 50.f), sf::Vector2f(1.5f, 1.5f), sf::Color::Blue, true));

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