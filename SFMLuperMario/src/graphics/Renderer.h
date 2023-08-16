#pragma once

#include <SFML/Graphics.hpp>
#include "../core/GameObject.h"

namespace Game
{
	namespace Graphics
	{
		class Renderer : public Game::Core::Component
		{
		public:
			int renderingOrder;

			virtual void start() override;
			void setTexture(std::string texPath, int x, int y, int spriteSize);
			sf::Sprite* prepareRendering();

			inline Renderer() : renderingOrder(0) {};
			~Renderer();

		private:
			sf::Sprite* sprite;
			sf::Texture* texture;
		};

		typedef std::shared_ptr<Renderer> PRenderer;
		typedef std::weak_ptr<Renderer> WPRenderer;
	}
}