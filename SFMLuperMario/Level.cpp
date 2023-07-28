#include <json.hpp>
#include <fstream>
#include "GameManager.h"
#include "Level.h"
#include "Utils.h"

Level::Level()
{

}

void Level::loadLevelData(int levelId)
{
	using json = nlohmann::json;

	std::string levelPath = "Assets/Levels/Level" + std::to_string(levelId) + ".json";
	std::ifstream f(levelPath);
	json data = json::parse(f);

	gravityForce = static_cast<float>(data.value("gravityForce", 240));
	floor = GameManager::getWindowSize().y - static_cast<float>(data.value("floor", 0));
	//std::string name = data.value("name", "not found");

	log(gravityForce);
	f.close();
}
