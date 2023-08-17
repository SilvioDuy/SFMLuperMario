#include "RenderingManager.h"
#include "Animator.h"
#include "../utils/Utils.h"

using namespace Game::Graphics;

Renderer::~Renderer()
{
	if (sprite)
		delete sprite;

	if (texture)
		delete texture;
}

void Renderer::start()
{
	texture = new sf::Texture();
	sprite = new sf::Sprite();

	WPRenderer renderer = gameObject->getComponent<Renderer>();
	RenderingManager::addRenderer(renderer);
}

void Renderer::onDestroy()
{
	RenderingManager::removeRenderer(this);
}

void Renderer::setTexture(std::string texPath, int x, int y, int width, int height)
{
	if (!texture->loadFromFile(texPath))
	{
		DEBUG_LOG("Didn't find texture: " << texPath << " for GameObject " << gameObject->name);
		return;
	}
		
	sprite->setTexture(*texture);
	sprite->setTextureRect(sf::IntRect(x, y, width, height));
	sf::Vector2f origin = sf::Vector2f(sprite->getScale().x * (float)width, sprite->getScale().y * (float)height) * 0.5f;
	sprite->setOrigin(origin);
}

sf::Sprite* Renderer::prepareRendering()
{
	auto transform = gameObject->transform;

	if (gameObject->transform)
	{
		sprite->setPosition(transform->position);
		sprite->setRotation(transform->rotation);
		sprite->setScale(transform->scale);
	}

	auto animator = gameObject->getComponent<Animator>();

	if (animator)
	{
		animator->animateSprite(*sprite);
	}

	return sprite;
}