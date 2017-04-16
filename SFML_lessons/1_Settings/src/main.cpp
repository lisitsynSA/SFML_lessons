#include <iostream>
#include "SFML/Graphics.hpp"

int main()
{
	std::cout << "SFML  START\n"; // -subsystem,windows in linker flags turn off console
	sf::RenderWindow window(sf::VideoMode(640, 480), "Test");

	while(window.isOpen()){

		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
			}

			window.clear();
			window.display();
		}
	}

	return 0;
}
