#include "PCH.h"
#include <SFML/Graphics.hpp>

using namespace mandr;

int main() {
	HexMapLayout layout = HexMapLayout(HexMap::Orientation_Horizontal, sf::Vector2f(24, 24), sf::Vector2f(64, 64));
	HexMap map(layout, 20, 20);

	// Render window with SFML
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Hex Test");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		map.draw(window);

		window.display();
	}
	
	return 0;
}