#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

void renderingThread(sf::RenderWindow* window);

int main()
{
	std::cout << "SFML  START\n"; // -subsystem,windows in linker flags turn off console

	//create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Graphics module");
	window.setVerticalSyncEnabled(true); // call it once, after creating the window

	// deactivate its OpenGL context
	window.setActive(false);

	// launch the rendering thread
	sf::Thread thread(&renderingThread, &window);
	thread.launch();

	// run the program as long as the window is open
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			 switch (event.type)
			{
				// "close requested" event: we close the window
				case sf::Event::Closed:
					window.close();
					std::cout << "[EVENT] Closed\n";
					break;

				case sf::Event::Resized:
					std::cout << "[EVENT] Resized new size: " << event.size.width << "x" << event.size.height << "\n";
					break;

				// we don't process other types of events
				default:
					break;
			}
		}
	}

	return 0;
}

void renderingThread(sf::RenderWindow* window)
{
//!!! Use as little textures as possible

// LOAD IMAGE
	sf::Texture treeTexture;
	if (!treeTexture.loadFromFile("../res/img1.png"))
	    std::cout << "[ERROR] Unable to load ../res/img1.png\n";
	else
	    std::cout << "[LOAD] ../res/img1.png\n";

	// Smoothing a texture makes pixel boundaries less visible
	treeTexture.setSmooth(true);
	// Allows a texture to be repeatedly tiled within a single sprite
	treeTexture.setRepeated(true);

	sf::Texture partTreeTexture;
	// load a 100x100 rectangle that starts at (10, 10)
	if (!partTreeTexture.loadFromFile("../res/img1.png", sf::IntRect(0, 0, 100, 100)))
	    std::cout << "[ERROR] Unable to load ../res/img1.png\n";
	else
	    std::cout << "[LOAD] ../res/img1.png\n";
	partTreeTexture.setRepeated(true);

// SPRITES
	sf::Sprite sprite;
	sf::Sprite colorSprite;
	sf::Sprite rotationSprite;
	sf::Sprite positionSprite;
	sf::Sprite scaleSprite;
	sf::Sprite partSprite;

	sprite.setTexture(treeTexture);
	sprite.setTextureRect(sf::IntRect(10, 10, 100, 100));
	sprite.setPosition(sf::Vector2f(50, 50));
	colorSprite.setTexture(treeTexture);
	colorSprite.setTextureRect(sf::IntRect(10, 10, 100, 100));
	colorSprite.setPosition(sf::Vector2f(250, 50));
	rotationSprite.setTexture(treeTexture);
	rotationSprite.setTextureRect(sf::IntRect(10, 10, 100, 100));
	rotationSprite.setPosition(sf::Vector2f(450, 50));
	positionSprite.setTexture(treeTexture);
	positionSprite.setTextureRect(sf::IntRect(10, 10, 100, 100));
	positionSprite.setPosition(sf::Vector2f(50, 250));
	scaleSprite.setTexture(treeTexture);
	scaleSprite.setTextureRect(sf::IntRect(10, 10, 100, 100));
	scaleSprite.setPosition(sf::Vector2f(250, 250));
	partSprite.setTexture(partTreeTexture);
	partSprite.setTextureRect(sf::IntRect(10, 10, 200, 200));
	partSprite.setPosition(sf::Vector2f(450, 250));

// When you set the texture of a sprite, all it does internally
// is store a pointer to the texture instance.
// Therefore, if the texture is destroyed or moves elsewhere in
// memory, the sprite ends up with an invalid texture pointer.

// FONTS
	sf::Font font;
	if (!font.loadFromFile("../res/Leters.ttf"))
	    std::cout << "[ERROR] Unable to load ../res/Leters.ttf\n";
	else
	    std::cout << "[LOAD] ../res/Leters.ttf\n";

	sf::Text text;
	// select the font
	text.setFont(font); // font is a sf::Font
	// set the string to display
	text.setString("Original sprite");
	// set the character size
	text.setCharacterSize(24); // in pixels, not points!
	// set the color
	text.setFillColor(sf::Color::Green);
	// set the text style
	text.setStyle(sf::Text::Bold);

	sf::Text rusText;
	rusText.setFont(font);
	rusText.setString("Ёффекты цвета");
	rusText.setCharacterSize(24);
	rusText.setFillColor(sf::Color::Red);
	rusText.setPosition(200, 0);


// RENDER TEXTURE
	// create a 500x500 render-texture
	sf::RenderTexture renderTexture;
	if (!renderTexture.create(600, 600))
	    std::cout << "[ERROR] Unable to renderTexture.create\n";

	// drawing uses the same functions
	renderTexture.clear();
	// draw everything here...
	// renderTexture.draw() or any other drawable
	renderTexture.draw(text);
	renderTexture.draw(rusText);

	text.setString("Rotation sprite");
	text.setPosition(400, 0);
	text.setFillColor(sf::Color::Blue);
	renderTexture.draw(text);
	text.setString("Position sprite");
	text.setPosition(0, 500);
	text.setFillColor(sf::Color::White);
	renderTexture.draw(text);
	text.setStyle(sf::Text::Regular);
	text.setString("Scale sprite");
	text.setPosition(200, 500);
	text.setFillColor(sf::Color::Cyan);
	renderTexture.draw(text);
	text.setString("Part/repeat sprite");
	text.setPosition(400, 500);
	text.setFillColor(sf::Color::Magenta);
	renderTexture.draw(text);
	renderTexture.display();

	// get the target texture (where the stuff has been drawn)
	// read-only texture
	const sf::Texture& texture = renderTexture.getTexture();

	// draw it to the window
	sf::Sprite renSprite(texture);

// RENDERING LOOP
	int step = 0;
    while (window->isOpen())
    {
		// clear the window with black color
		window->clear(sf::Color::Black);

// SRITE EFFECTS
		// color
		//The color that you set is modulated (multiplied) with the texture of the sprite
		colorSprite.setColor(sf::Color(step*2, 255 - step, 255 - step*2));

		// rotation
		//sprite.setOrigin(sf::Vector2f(160, 180));
		if (step%100 == 0)
			rotationSprite.setRotation(0); // absolute angle
		rotationSprite.rotate(1); // offset relative to the current angle

		// position
		if (step%100 == 0)
			positionSprite.setPosition(sf::Vector2f(50, 250)); // absolute position
		positionSprite.move(sf::Vector2f(1, 1)); // offset relative to the current position

		// scale
		if (step%100 == 0)
			scaleSprite.setScale(sf::Vector2f(1.f, 1.f)); // absolute scale factor
		scaleSprite.scale(sf::Vector2f(1.1f, 0.9f)); // factor relative to the current scale

		// draw everything here...
		// window.draw(...);
		window->draw(renSprite);
		window->draw(sprite);
		window->draw(colorSprite);
		window->draw(rotationSprite);
		window->draw(positionSprite);
		window->draw(scaleSprite);
		window->draw(partSprite);

		// end the current frame
        window->display();
        step++;
    }
}
