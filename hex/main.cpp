#include "PCH.h"
#include <SFML/Graphics.hpp>

int main() {
	
	mandr::Map map(6, 6);

	for (int i = -6; i < 6; i++) {
		for (int j = -8; j < 8; j++) {
			mandr::Hex* h = map.getHex(i, j);
			if (h != NULL) {
				std::cout << *h << std::endl;
			}
		}
	}

	std::cout << "The distance between (0,5) and (5,1) is " << mandr::Hex::distance(mandr::Hex(0, 5), mandr::Hex(5,1)); // 5
	std::cout << "The distance between (0,0) and (3,5) is " << mandr::Hex::distance(mandr::Hex(0, 0), mandr::Hex(3, 5)); // 8
	std::cout << "The distance between (0,2) and (2,3) is " << mandr::Hex::distance(mandr::Hex(0, 2), mandr::Hex(2, 3)); // 3
	std::cout << "The distance between (-1,4) and (0,4) is " << mandr::Hex::distance(mandr::Hex(-1, 4), mandr::Hex(0, 4)); // 1

	// std::vector<std::vector<mandr::Hex>> hexes;
	// for (int i = 0; i < 8; i++) {
	// 	std::vector<mandr::Hex> col;
	// 	for (int j = 0; j < 8; j++) {
	// 		col.push_back(mandr::Hex(i, j, 50, mandr::Hex::HEX_TYPE_HORIZONTAL));
	// 	}
	// 	hexes.push_back(col);
	// }

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