#include <json.hpp>
#include <fstream>
#include "Level.h"

Level::Level()
{

}

void Level::loadLevel(int levelId)
{
	using json = nlohmann::json;

	std::string levelPath = "Assets/Levels/Level" + std::to_string(levelId) + ".json";
	std::ifstream f(levelPath);
	json data = json::parse(f);
	std::string name = data.value("name", "not found");

	log(name);
}
