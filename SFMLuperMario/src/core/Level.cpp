#include <json.hpp>
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
		log("[Error] Failed to open file for Level " << levelId);
		return;
	}

	json data = json::parse(f);

	gravityForce = static_cast<float>(data.value("gravityForce", 240));
	floor = GameManager::getWindowSize().y - static_cast<float>(data.value("floor", 0));

	f.close();
}
