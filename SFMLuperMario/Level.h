#pragma once

#include <SFML\Graphics.hpp>
#include "Utils.h"

class Level
{
	struct Tile
	{
		sf::Sprite sprite;
		sf::Texture texture;
	};

public:

	void loadLevel(int levelId);
	void populateTiles();

	Level();

private:

	std::vector<Tile> tiles;

};

