#include "Hex.h"
#include "PCH.h"

namespace mandr {
	Hex::Hex(int q, int r) : q(q), r(r) { }

	Hex::~Hex() {

	}

	sf::Vector3i Hex::toCube(Hex& h) {
		int x = h.q;
		int z = h.r;
		int y = -x - z;
		
		return sf::Vector3i(x, y, z);
	}

	int Hex::cube_distance(sf::Vector3i a, sf::Vector3i b) {
		return std::max(std::abs(a.x - b.x), std::max(std::abs(a.y - b.y), std::abs(a.z - b.z)));
	}

	int Hex::distance(Hex& a, Hex& b) {
		sf::Vector3i ac = toCube(a);
		sf::Vector3i bc = toCube(b);
		return cube_distance(ac, bc);
	}

	void Hex::draw(sf::RenderWindow& window) {
		// sf::CircleShape hexShape(size, 6);
		// hexShape.setPosition(center.x, center.y);
		// 
		// hexShape.setFillColor(sf::Color::White);
		// 
		// window.draw(hexShape);
	}

	std::ostream& operator<<(std::ostream& os, Hex h) {
		os << "{ " << h.q << ", " << h.r << "}";
		return os;
	}
}
