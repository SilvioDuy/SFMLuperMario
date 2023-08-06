// SFMLSetup.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <SFML\Graphics.hpp>
#include "src/core/GameManager.h"
#include "src/core/Entity.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(640, 400), "SFML works!", Style::Default);
    window.setFramerateLimit(60);

    Game::Core::GameManager gameManager(&window);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        gameManager.updateGame();

#pragma region Draw

        window.clear();

        for (auto const& e : Game::Core::GameManager::getEntities())
        {
            if (e == nullptr)
                continue;

            window.draw(e->getSprite());
        }

        window.display();

#pragma endregion        
    }

    return 0;
}
