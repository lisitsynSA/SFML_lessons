#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

void inputDevicesStatus(sf::Window * window);

int main()
{
	std::cout << "SFML  START\n"; // -subsystem,windows in linker flags turn off console


	/// WINDOW
	//create Window
	sf::Window window(sf::VideoMode(800, 600), "Window module");
	window.setVerticalSyncEnabled(true); // call it once, after creating the window

	// create task for printing status
	sf::Thread thread(&inputDevicesStatus, &window);
	thread.launch();

	sf::sleep(sf::seconds(1));

	// change the position of the window (relatively to the desktop)
	window.setPosition(sf::Vector2i(10, 50));

	sf::sleep(sf::seconds(1));

	// change the size of the window
	window.setSize(sf::Vector2u(640, 480));

	sf::sleep(sf::seconds(1));

	// change the title of the window
	window.setTitle("SFML window");

	sf::sleep(sf::seconds(1));

	// run the program as long as the window is open
	while (window.isOpen())
	{

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		sf::Vector2u size;
		while (window.pollEvent(event))
		{
	/// EVENT
			 switch (event.type)
			{
				// "close requested" event: we close the window
				case sf::Event::Closed:
					// get the size of the window
					size = window.getSize();
					window.close();
					std::cout << "[EVENT] Closed\nSIZE OF WINDOW: " << size.x << "x" << size.y << "\n";
					break;

			/// KEY
				case sf::Event::KeyPressed:
					std::cout << "[EVENT] KeyPressed\n";
					if (event.key.code == sf::Keyboard::Escape){
						std::cout << "the escape key was pressed\n";
						std::cout << "control:" << event.key.control << "\n";
						std::cout << "alt:" << event.key.alt << "\n";
						std::cout << "shift:" << event.key.shift << "\n";
						std::cout << "system:" << event.key.system << "\n";
					}
					break;

				case sf::Event::KeyReleased:
					std::cout << "[EVENT] KeyReleased\n";
					break;

				case sf::Event::TextEntered:
					std::cout << "[EVENT] TextEntered\n";
					if (event.text.unicode < 128)
						std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << "\n";
					break;

			/// MOUSE
				case sf::Event::MouseWheelScrolled:
					std::cout << "[EVENT] MouseWheelScrolled\n";
					if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
						std::cout << "wheel type: vertical\n";
					else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
						std::cout << "wheel type: horizontal\n";
					else
						std::cout << "wheel type: unknown\n";;
					std::cout << "wheel movement: " << event.mouseWheelScroll.delta << "\n";
					std::cout << "mouse x: " << event.mouseWheelScroll.x << "\n";
					std::cout << "mouse y: " << event.mouseWheelScroll.y << "\n";
					break;

				case sf::Event::MouseButtonPressed:
					std::cout << "[EVENT] MouseButtonPressed\n";
					if (event.mouseButton.button == sf::Mouse::Right)
						std::cout << "the right button was pressed\n";
					if (event.mouseButton.button == sf::Mouse::Left)
						std::cout << "the left button was pressed\n";
					if (event.mouseButton.button == sf::Mouse::Middle)
						std::cout << "the middle button was pressed\n";
					std::cout << "mouse x: " << event.mouseButton.x << "\n";
					std::cout << "mouse y: " << event.mouseButton.y << "\n";
					break;

				case sf::Event::MouseMoved:
					std::cout << "[EVENT] MouseMoved (" << event.mouseMove.x << "," << event.mouseMove.y << ")";
					break;

				case sf::Event::MouseEntered:
					std::cout << "[EVENT] MouseEntered\n";
					break;
				case sf::Event::MouseLeft:
					std::cout << "[EVENT] MouseLeft\n";
					break;

			/// WINDOW
				case sf::Event::Resized:
					std::cout << "[EVENT] Resized new size: " << event.size.width << "x" << event.size.height << "\n";
					break;

				case sf::Event::LostFocus:
					std::cout << "[EVENT] LostFocus\n";
					break;

				case sf::Event::GainedFocus:
					std::cout << "[EVENT] GainedFocus\n";
					break;

				// we don't process other types of events
				default:
					break;
			}
		}
	}

	return 0;
} // thread.wait()

// KEYBOARD MOUSE STATUS
// Get data even with lost focus
void inputDevicesStatus(sf::Window * window)
{
	while(window->isOpen())
	{
		sf::sleep(sf::seconds(5));
		std::cout << "[STATUS]\n";
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			std::cout << "KEY Left is pressed\n";
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			std::cout << "KEY Right is pressed\n";
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			std::cout << "MOUSE Left button is pressed\n";
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			std::cout << "MOUSE Right button is pressed\n";

		// get the global mouse position (relative to the desktop)
		sf::Vector2i globalPosition = sf::Mouse::getPosition();
		std::cout << "MOUSE GLOBAL POSITION (" << globalPosition.x << ", " <<  globalPosition.y << ")\n";
		// get the local mouse position (relative to a window)
		sf::Vector2i localPosition = sf::Mouse::getPosition(*window); // window is a sf::Window
		std::cout << "MOUSE LOCAL POSITION (" << localPosition.x << ", " <<  localPosition.y << ")\n";
	}
}
