#include "Hex.h"
#include "PCH.h"

namespace mandr {
	Hex::Hex(Map* pMap, int col, int row) : m_pMap(pMap), m_Coords(col, row) { }

	Hex::~Hex() { }

	sf::Vector3i Hex::even_r_to_cube(int q, int r) {
		int x = q - (r + (r & 1)) / 2;
		int z = r;
		int y = -x - z;
		
		return sf::Vector3i(x, y, z);
	}


	sf::Vector3i Hex::even_r_to_cube(const Coordinates& c) {
		return even_r_to_cube(c.q, c.r);
	}

	Hex::Coordinates Hex::cube_to_even_r(int x, int y, int z) {
		int q = x + (z + (z & 1)) / 2;
		int r = z;
		return Coordinates(q,r);
	}

	int Hex::cube_distance(const sf::Vector3i a, const sf::Vector3i b) {
		return std::max(std::abs(a.x - b.x), std::max(std::abs(a.y - b.y), std::abs(a.z - b.z)));
	}

	int Hex::distance(const Hex& a, const Hex& b) {
		sf::Vector3i ac = even_r_to_cube(a.m_Coords.q, a.m_Coords.r);
		sf::Vector3i bc = even_r_to_cube(b.m_Coords.q, b.m_Coords.r);
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
		return m_pMap->getHex(m_Coords.q + offset_q, m_Coords.r + offset_r);
	}

	std::ostream& operator<<(std::ostream& os, Hex h) {
		os << "{ " << h.m_Coords.q << ", " << h.m_Coords.r << "}";
		return os;
	}

	Hex::Coordinates operator+(const Hex::Coordinates& a, const Hex::Coordinates& b) {
		Hex::Coordinates c = a;
		c += b;
		return c;
	}

	Hex::Coordinates& Hex::Coordinates::operator+=(const Hex::Coordinates& other) {
		// Convert to cube
		sf::Vector3i c_a = Hex::even_r_to_cube(*this);
		sf::Vector3i c_b = Hex::even_r_to_cube(other);

		// Perform addition, then convert back to offset
		Coordinates c = cube_to_even_r(c_a.x + c_b.x, c_a.y + c_b.y, c_a.z + c_b.z);

		// Update the coordinates
		q = c.q;
		r = c.r;

		return *this;
	}
}
