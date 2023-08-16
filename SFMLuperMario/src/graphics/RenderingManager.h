#pragma once

#include <vector>
#include "Renderer.h"

namespace Game
{
	namespace Graphics
	{
		class RenderingManager
		{
		public:
			void renderFrame(sf::RenderWindow& window);

			static void addRenderer(WPRenderer renderer);
			static void removeRenderer(const Renderer* renderer);

			RenderingManager();
			~RenderingManager();

		private:
			static std::vector<WPRenderer> renderers;
		};
	}
}