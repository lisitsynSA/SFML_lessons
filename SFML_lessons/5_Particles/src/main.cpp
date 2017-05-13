#include <iostream>

#include "SFML/Graphics.hpp"
#include "ParticleSystem.h"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(512, 256), "Particles");

    // create the particle system
    ParticleSystem particles(10000);

    // create a clock to track the elapsed time
    sf::Clock clock;

    std::cout << "Left = Random speed\nRight = Random lifetime\nMiddle = Color\n";
    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
        	if (event.type == sf::Event::MouseButtonPressed)
                particles.pressedButton(1 << event.mouseButton.button);
        	if (event.type == sf::Event::MouseButtonReleased)
        	    particles.releasedButton(1 << event.mouseButton.button);
        	if (event.type == sf::Event::MouseWheelScrolled)
        		particles.changeScale(event.mouseWheelScroll.delta);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // make the particle system emitter follow the mouse
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        // update it
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        // draw it
        window.clear();
        window.draw(particles);
        window.display();
    }

    return 0;
}
