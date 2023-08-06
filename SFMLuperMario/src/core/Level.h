#pragma once

#include <SFML\Graphics.hpp>

namespace Game
{
	namespace Core
	{
		class Level
		{
			/// <summary>
			/// Representation of a tile
			/// </summary>
			struct Tile
			{
				sf::Sprite sprite;
				sf::Texture texture;
			};

		public:
			/// <summary>
			/// Loads level data from file
			/// </summary>
			/// <param name="levelId"></param>
			void loadLevelData(int levelId);
			/// <summary>
			/// Populates all the level tiles
			/// </summary>
			void populateTiles();
			/// <summary>
			/// Get level gravity force
			/// </summary>
			/// <returns>Gravity force</returns>
			inline float getGravityForce() { return gravityForce; }
			/// <summary>
			/// Get level gravity force
			/// </summary>
			/// <returns>Gravity force</returns>
			inline float getFloorHeight() { return floor; }

			Level();

		private:
			/// <summary>
			/// All the tiles of this level
			/// </summary>
			std::vector<Tile> tiles;
			/// <summary>
			/// Gravity force for this level
			/// </summary>
			float gravityForce;
			/// <summary>
			/// Floor height
			/// </summary>
			float floor;
		};
	}
}