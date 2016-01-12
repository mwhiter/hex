#include "Hex.h"
#include "PCH.h"

namespace mandr {
	Hex::Hex(HexMap* pMap, int col, int row) : m_pMap(pMap), m_Coords(col, row) { }

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

	Hex::Coordinates Hex::cube_round(double x, double y, double z)
	{
		double rx = round(x);
		double ry = round(y);
		double rz = round(z);

		double xd = abs(rx - x);	// xd = x difference
		double yd = abs(ry - y);
		double zd = abs(rz - z);

		if (xd > yd && xd > zd)
			rx = -ry - rz;
		else if (yd > zd)
			ry = -rx - rz;
		else
			rz = -rx - ry;

		return Hex::Coordinates(cube_to_even_r(rx,ry,rz));
	}

	int Hex::cube_distance(const sf::Vector3i a, const sf::Vector3i b) {
		return std::max(std::abs(a.x - b.x), std::max(std::abs(a.y - b.y), std::abs(a.z - b.z)));
	}

	int Hex::distance(const Hex& a, const Hex& b) {
		sf::Vector3i ac = even_r_to_cube(a.m_Coords.q, a.m_Coords.r);
		sf::Vector3i bc = even_r_to_cube(b.m_Coords.q, b.m_Coords.r);
		return cube_distance(ac, bc);
	}

	void Hex::draw(const HexMapLayout& layout, sf::Window& window) const {
	}

	sf::Vector2i Hex::hex_to_pixel(const HexMapLayout & layout) {
		const HexMapOrientation& o = layout.o;
		int q = m_Coords.q, r = m_Coords.r;
		double x = (o.f0 * q + o.f1 * r) * layout.size.x;
		double y = (o.f2 * q + o.f3 * r) * layout.size.y;
		return sf::Vector2i(x + layout.origin.x, y + layout.origin.y);
	}

	Hex::Coordinates Hex::pixel_to_hex(const HexMapLayout & layout, sf::Vector2i & p)
	{
		const HexMapOrientation& o = layout.o;
		sf::Vector2f pt = sf::Vector2f((p.x - layout.origin.x) / layout.size.x,
									   (p.y - layout.origin.y) / layout.size.y);
		double q = o.b0 * pt.x + o.b1 * p.y;
		double r = o.b2 * pt.x + o.b3 * p.y;
		return Hex::Coordinates(cube_round(q, r, -q-r));	// convert cubic to even_r offset coords
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
