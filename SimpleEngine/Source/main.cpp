// Define SFML to be linked as a static libary with the exe
#define SFML_STATIC 

// Relevant includes for SFML graphics
#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 960), "Test Code");
	sf::RectangleShape  rect_shape({50, 50});
	rect_shape.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(rect_shape);
		window.display();
	}

	return 0;
}