#include "Tile.h"

namespace mandr {

	Tile::Tile(int x, int y) : m_X(x), m_Y(y) {
		// This is a test. Ideally, I'd load all the images in a map loading function (after we've gotten tile types and then update when changed)
		// Also, I'd probably want an array of textures that are first loaded in, and then we refer to that array instead of constantly loading in textures (wasteful)
		assert(m_Texture.loadFromFile("../../../res/grass512.png"));
	}

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
	sf::Texture Tile::getTexture() const
	{
		return m_Texture;
	}
}