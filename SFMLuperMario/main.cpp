// SFMLSetup.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <SFML\Graphics.hpp>
#include "src/core/GameManager.h"
#include "src/physics/PhysicsManager.h"
#include "src/graphics/RenderingManager.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(640, 400), "SFML works!", Style::Default);
    window.setFramerateLimit(60);

    Game::Core::GameManager gameManager(&window);
    Game::Physics::PhysicsManager physicsManager;
    Game::Graphics::RenderingManager renderingManager;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        gameManager.updateGame();

        physicsManager.resolvePhysics();

        renderingManager.renderFrame(window);
    }

    return 0;
}
