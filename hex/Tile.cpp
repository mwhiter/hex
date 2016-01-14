#include "Tile.h"

namespace mandr {

	Tile::Tile(int x, int y) : m_X(x), m_Y(y) { }

	Tile::~Tile() { }

	int Tile::getX() const {
		return m_X;
	}

	int Tile::getY() const {
		return m_Y;
	}

	Hex Tile::getHex() const {
		return Hex::even_r_to_cube(sf::Vector2i(m_X, m_Y));
	}
}