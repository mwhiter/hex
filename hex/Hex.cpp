#include "Hex.h"
#include "PCH.h"

namespace mandr {

	const Hex Hex::neighbors[NUM_DIRECTIONS] = {
		Hex(1, 0, -1),	// NE
		Hex(1, -1, 0),	// E
		Hex(1, -1, 0),	// SE
		Hex(0, -1, 1),	// SW
		Hex(-1, 1, 0),	// W
		Hex(1, 0, -1),	// NW
	};

	Hex Hex::even_r_to_cube(const sf::Vector2i& v)
	{
		return Hex(v.x - (v.y + (v.x & 1)) / 2, v.y);
	}

	sf::Vector2i Hex::cube_to_even_r(const Hex & a) {
		int q = a.q + (a.s + (a.s & 1)) / 2;
		int r = a.s;
		return sf::Vector2i(q, r);
	}

	Hex Hex::round(float x, float y, float z) {
		float rx = std::round(x);
		float ry = std::round(y);
		float rz = std::round(z);

		float xd = abs(rx - x);
		float yd = abs(ry - y);
		float zd = abs(rz - z);

		if (xd > yd && xd > zd)
			rx = -ry - rz;
		else if (yd > zd)
			ry = -rx - rz;
		else
			rz = -rx - ry;
		
		return Hex((int)rx, (int)ry, (int)rz);
	}

	void Hex::draw(const HexMapLayout& layout, sf::RenderWindow& window) const {
		std::vector<sf::Vector2f> corners = polygon_corners(layout);

		sf::VertexArray lines(sf::LinesStrip, 7);
		for (int i = 0; i < 7; i++) {
			lines[i] = corners[i % 6];
		}
		window.draw(lines);
	}

	sf::Vector2f Hex::hex_to_pixel(const Hex& h, const HexMapLayout & layout) {
		const HexMapOrientation& o = layout.orientation;
		double x = (o.f0 * h.q + o.f1 * h.r) * layout.size.x;
		double y = (o.f2 * h.q + o.f3 * h.r) * layout.size.y;
		return sf::Vector2f((float) x + layout.origin.x, (float) y + layout.origin.y);
	}

	Hex Hex::pixel_to_hex(const HexMapLayout & layout, sf::Vector2i & p)
	{
		const HexMapOrientation& o = layout.orientation;
		sf::Vector2f pt = sf::Vector2f((p.x - layout.origin.x) / layout.size.x,
									   (p.y - layout.origin.y) / layout.size.y);
		double q = o.b0 * pt.x + o.b1 * p.y;
		double r = o.b2 * pt.x + o.b3 * p.y;
		return round(q, r, -q - r);
	}

	// Get tile adjacent in any direction
	Hex Hex::getAdjacent(const Hex& h, DirectionType direction) const {
		assert(direction > NO_DIRECTION && direction < NUM_DIRECTIONS);
		return h + neighbors[direction];
	}

	std::ostream& operator<<(std::ostream& os, Hex h) {
		os << "{ " << h.q << ", " << h.r << ", " << h.s << "}";
		return os;
	}

	bool operator==(const Hex& a, const Hex& b) {
		return a.q == b.q && a.r == b.r && a.s == b.s;
	}

	Hex operator+(const Hex & a, const Hex & b)
	{
		Hex c = a;
		c += b;
		return c;
	}

	Hex& Hex::operator+=(const Hex& other) {
		q += other.q;
		r += other.r;
		s += other.s;
		
		assert(q + r + s == 0);

		return *this;
	}

	Hex operator-(const Hex& a, const Hex& b) {
		Hex c = a;
		c -= b;
		return a;
	}

	Hex& Hex::operator-=(const Hex& other) {
		q -= other.q;
		r -= other.r;
		s -= other.s;

		assert(q + r + s == 0);

		return *this;
	}

	Hex operator*(const Hex& a, int k) {
		Hex b = a;
		b *= k;
		return b;
	}

	Hex& Hex::operator*=(int k) {
		q *= k;
		r *= k;
		s *= k;
		
		assert(q + r + s == 0);

		return *this;
	}

	int Hex::length(const Hex& a) {
		return int((abs(a.q) + abs(a.r) + abs(a.s)) / 2);
	}

	int Hex::distance(const Hex & a, const Hex & b)
	{
		return length(a - b);
	}

	sf::Vector2f Hex::corner_offset(const HexMapLayout& layout, int corner) const {
		sf::Vector2f size = layout.size;
		double angle = 2.0 * M_PI * (corner + layout.orientation.start_angle) / 6;
		return sf::Vector2f(size.x * cos(angle), size.y * sin(angle));
	}

	std::vector<sf::Vector2f> Hex::polygon_corners(const HexMapLayout& layout) const {
		std::vector<sf::Vector2f> corners = {};
		sf::Vector2f center = hex_to_pixel(*this, layout);
		for (int i = 0; i < 6; i++) {
			sf::Vector2f offset = corner_offset(layout, i);
			corners.push_back(sf::Vector2f(center.x + offset.x, center.y + offset.y));
		}
		return corners;
	}
}
