#include <iostream>

#include "SFML/Graphics.hpp"
#include "TileMap.h"

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");

	// define the level with an array of tile indices
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};

	// create the tilemap from the level definition
	TileMap map;
	if (!map.load("res/tileset.png", sf::Vector2u(32, 32), level, 16, 8))
		return -1;

	// create a view with the rectangular area of the 2D world to show
	float size_x = 512;
	float size_y = 256;
	sf::View view(sf::FloatRect(0, 0, size_x, size_y));
	// activate it
	window.setView(view);

	// run the main loop
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
        	if (event.type == sf::Event::MouseWheelScrolled)
        	{
        		size_x += 4*event.mouseWheelScroll.delta;
        		size_y += 2*event.mouseWheelScroll.delta;
        		view.setSize(size_x, size_y);
        		std::cout << "[Wheel] (" << size_x << ", " << size_y << ")\n";
        	}
        	if (event.type == sf::Event::KeyPressed)
        		switch (event.key.code)
        		{
        		case sf::Keyboard::Up:
        			view.move(0, -10);
        			break;
        		case sf::Keyboard::Down:
        			view.move(0, 10);
        			break;
        		case sf::Keyboard::Left:
        			view.move(-10, 0);
        			break;
        		case sf::Keyboard::Right:
        			view.move(10, 0);
        			break;
        		case sf::Keyboard::PageDown:
        			view.rotate(1);
        			break;
        		case sf::Keyboard::PageUp:
        			view.rotate(-1);
        			break;
        		default:
        			break;
        		}
		}
		// draw the map
		window.clear();
		window.draw(map);
		window.setView(view);
		window.display();
	}
    return 0;
}
