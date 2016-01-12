#include "PCH.h"
#include <SFML/Graphics.hpp>

using namespace mandr;

int main() {
	
	// HexMap map(10, 10);
	// 
	// Hex* hex = map.getHex(0, 3)->getAdjacent(DirectionType::DIRECTION_NORTHEAST);
	// std::cout << *hex << std::endl;
	// 
	// hex = hex->getAdjacent(DirectionType::DIRECTION_SOUTHEAST);
	// std::cout << *hex << std::endl;
	// 
	// std::vector<Hex*> v = map.getHexesInRange(mandr::Hex::Coordinates(3,3), 2);
	// std::cout << "size of v: " << v.size() << std::endl;
	// 
	// std::vector<Hex*>::iterator it;
	// for (it = v.begin(); it != v.end(); it++) {
	// 	std::cout << **it << " " << std::endl;
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

		// for (int q = 0; q < map.getWidth(); q++) {
		// 	for (int r = 0; r < map.getHeight(); r++) {
		// 		sf::CircleShape hex(25, 6);
		// 
		// 		const HexMap::Orientation& o = HexMap::Orientation_Horizontal;
		// 
		// 		sf::Vector3i cube_c = Hex::even_r_to_cube(q, r);
		// 
		// 		double x = (o.f0 * cube_c.x + o.f1 * cube_c.z) * -25;
		// 		double y = (o.f2 * cube_c.x + o.f3 * cube_c.z) * -25;
		// 
		// 		hex.setOrigin(x - 100, y - 100);
		// 
		// 		//hex.setOutlineColor(sf::Color::Yellow);
		// 		//hex.setFillColor(sf::Color::Blue);
		// 		hex.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		// 
		// 		window.draw(hex);
		// 	}
		// }

		window.display();
	}

	system("PAUSE");
	
	return 0;
}