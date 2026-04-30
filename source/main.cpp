#include <iostream>
#include "SFML/Graphics.hpp"

#include "Game.h"

sf::RenderWindow* window;
Game* game;

int WinMain()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Fairy Wizard", sf::Style::Close);

	game = new Game();
	game->Setup();

	sf::Clock deltaClock;
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				break;
			}
		}

		window->clear();

		sf::Time deltaTime = deltaClock.restart();
		game->Run(deltaTime.asSeconds());
		game->Render(window);

		window->display();
	}

	delete window;
	delete game;

	return EXIT_SUCCESS;
}