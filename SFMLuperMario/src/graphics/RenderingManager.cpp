#include "RenderingManager.h"

using namespace Game::Graphics;

std::vector<WPRenderer> RenderingManager::renderers;

RenderingManager::RenderingManager()
{

}

RenderingManager::~RenderingManager()
{
	renderers.clear();
}

void RenderingManager::renderFrame(sf::RenderWindow& window)
{
	window.clear();

	for (auto const& renderer : renderers)
	{		
		if (auto r = renderer.lock())
		{
			if (!r->enabled)
				continue;

			auto sprite = r->prepareRendering();
			window.draw(*sprite);
		}
	}

	window.display();
}

void RenderingManager::addRenderer(WPRenderer renderer)
{
	if (auto rendererToAdd = renderer.lock())
	{
		if (renderers.begin() >= renderers.end())
		{
			renderers.push_back(std::move(renderer));
			return;
		}

		int id = -1;
		unsigned int i = 0;

		while (id < 0 && i < renderers.size())
		{
			if (auto r = renderers[i].lock())
			{
				if (r->renderingOrder >= rendererToAdd->renderingOrder)
				{
					id = i;
				}
			}

			i++;
		}

		auto iteratorPos = renderers.begin() + id;

		renderers.insert(iteratorPos, std::move(renderer));
	}
}

void RenderingManager::removeRenderer(const Renderer* renderer)
{
	if (renderer == nullptr)
		return;

	int index = -1;

	for (unsigned int i = 0; i < renderers.size(); i++)
	{
		if (auto r = renderers[i].lock())
		{
			if (r.get() == renderer)
			{
				index = i;
				break;
			}
		}
	}

	if (index < 0)
		return;

	renderers.erase(renderers.begin() + index);
}