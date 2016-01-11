#include "Hex.h"
#include "PCH.h"

namespace mandr {
	Hex::Hex(Map* m, int q, int r) : pMap(m), q(q), r(r) { }

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

	// Get tile adjacent in any direction
	Hex* Hex::getAdjacent(DirectionType direction) const {
		int offset_q, offset_r;
		switch (direction) {
			case DIRECTION_NORTHEAST:	offset_q = 1, offset_r = -1; break;
			case DIRECTION_EAST:		offset_q = 1, offset_r = 0; break;
			case DIRECTION_SOUTHEAST:	offset_q = 0, offset_r = 1; break;
			case DIRECTION_SOUTHWEST:	offset_q = -1, offset_r = 1; break;
			case DIRECTION_WEST:		offset_q = -1, offset_r = 0; break;
			case DIRECTION_NORTHWEST:	offset_q = 0, offset_r = -1; break;
			default: return NULL;
		}
		return pMap->getHex(q + offset_q, r + offset_r);
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
