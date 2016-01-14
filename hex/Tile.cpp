#include "Tile.h"

namespace mandr {

	Tile::Tile(int x, int y) : x(x), y(y) { }

	Tile::~Tile() { }

	Hex Tile::getHex() const {
		return Hex::even_r_to_cube(sf::Vector2i(x, y));
	}
}