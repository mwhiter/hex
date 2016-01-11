#include "PCH.h"
#include <SFML/Graphics.hpp>

int main() {
	
	mandr::Map map(6, 6);

	mandr::Hex* hex = map.getHex(0, 3)->getAdjacent(mandr::DirectionType::DIRECTION_NORTHEAST);
	std::cout << *hex << std::endl;

	hex = hex->getAdjacent(mandr::DirectionType::DIRECTION_SOUTHEAST);
	std::cout << *hex << std::endl;

	// Render window with SFML
	sf::RenderWindow window(sf::VideoMode(640, 640), "Hex Test");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// for (int i = 0; i < hexes.size(); i++) {
		// 	for (int j = 0; j < hexes.size(); j++) {
		// 		hexes[i][j].draw(window);
		// 	}
		// }
		//window.draw(shape);

		window.display();
	}

	return 0;
}