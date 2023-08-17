#include <fstream>
#include "GameManager.h"
#include "Level.h"
#include "GameObject.h"
#include "../graphics/Renderer.h"
#include "../physics/PhysicsHandler.h"
#include "../utils/Utils.h"
#include "../utils/AssetsUtils.h"

using namespace Game::Core;

Level::~Level()
{
	for (int i = tiles.size() - 1; i >= 0; i--)
	{
		tiles[i]->destroy();
	}

	tiles.clear();
}

void Level::loadLevelData(int levelId)
{
	using json = nlohmann::json;

	std::string levelPath = LEVELS_DIR + std::to_string(levelId) + LEVEL_EXTENSION;
	std::ifstream f(levelPath);

	if (!f)
	{
		DEBUG_LOG("[Error] Failed to open file for Level " << levelId);
		return;
	}

	json data = json::parse(f);

	gravityForce = static_cast<float>(data.value("gravityForce", 240));
	floor = GameManager::getWindowSize().y - static_cast<float>(data.value("floor", 0));

	auto& tiles = data["tiles"];

	populateTiles(tiles);

	f.close();
}

void Level::populateTiles(const nlohmann::json& tilesData)
{
	unsigned int i = 0;

	for (auto& tileData : tilesData)
	{
		auto pos = sf::Vector2f(tileData["position"].value("x", 0), GameManager::getOriginalY(tileData["position"].value("y", 0)));
		auto scale = sf::Vector2f(tileData["scale"].value("x", 0), tileData["scale"].value("y", 0));
		float rotation = tileData.value("rotation", 0.f);
		sf::Vector2i texCoord = sf::Vector2i(tileData["texCoord"].value("x", 0), tileData["texCoord"].value("y", 0));
		sf::Vector2i texSize = sf::Vector2i(tileData["texSize"].value("x", 0), tileData["texSize"].value("y", 0));

		GameObject* tileGO = GameObject::instantiate("Tile_" + i);

		tileGO->transform->position = pos;
		tileGO->transform->scale = scale;
		tileGO->transform->rotation = rotation;

		bool isSolid = tileData.value("solid", false);
		if (isSolid)
		{
			Game::Physics::PhysicsHandler* ph = new Game::Physics::PhysicsHandler(pos, true, false);
			ph->collider->size = sf::Vector2f(texSize.x, texSize.y);

			tileGO->addComponent<Game::Physics::PhysicsHandler>(ph);
		}

		std::string texturePath = tileData.value("texture", "");

		if (texturePath == "")
			continue;

		auto renderer = tileGO->addComponent<Game::Graphics::Renderer>();

		renderer->setTexture(texturePath, texCoord.x, texCoord.y, texSize.x, texSize.y);

		tiles.push_back(tileGO);

		i++;
	}
}