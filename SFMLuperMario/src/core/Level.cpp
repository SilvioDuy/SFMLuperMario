#include <fstream>
#include "GameManager.h"
#include "Level.h"
#include "../utils/Utils.h"
#include "../utils/AssetsUtils.h"

using namespace Game::Core;

Level::Level()
{

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
	for (auto& tileData : tilesData)
	{
		auto pos = sf::Vector2i(tileData["position"].value("x", 0), tileData["position"].value("y", 0));
		auto scale = sf::Vector2f(tileData["scale"].value("x", 0), tileData["scale"].value("y", 0));
		float rotation = tileData.value("rotation", 0.f);

		PTile tile = std::shared_ptr<Tile>(new Tile(pos, scale, rotation));
		
		tile->isInteractable = tileData.value("interactable", false);
		tile->isSolid = tileData.value("solid", false);

		std::string texturePath = tileData.value("texture", "");

		if (!tile->texture->loadFromFile(texturePath))
		{
			DEBUG_LOG("Didn't find texture: " << texturePath << " for entity tile");
			return;
		}

		sf::Vector2i texCoord = sf::Vector2i(tileData["texCoord"].value("x", 0), tileData["texCoord"].value("y", 0));
		sf::Vector2i texSize = sf::Vector2i(tileData["texSize"].value("x", 0), tileData["texSize"].value("y", 0));

		tile->sprite->setTexture(*tile->texture);
		tile->sprite->setTextureRect(sf::IntRect(texCoord, texSize));
		tile->sprite->setOrigin(sf::Vector2f(texSize.x * 0.5f, texSize.y * 0.5f));

		tiles.push_back(std::move(tile));
	}
}

Level::Tile::Tile(sf::Vector2i position, sf::Vector2f scale, float rotation)
{
	sprite = new sf::Sprite();
	texture = new sf::Texture();

	sprite->setPosition(sf::Vector2f(position.x, GameManager::getOriginalY(position.y)));
	sprite->setScale(scale);
	sprite->setRotation(rotation);

	isInteractable = false;
	isSolid = false;
}

Level::Tile::~Tile()
{
	delete sprite;
	delete texture;
}