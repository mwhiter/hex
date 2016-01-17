#include "Tile.h"
#include <iostream>
#include "Application.h"

namespace mandr {

	Tile::Tile(HexMap* pMap, int x, int y) : m_X(x), m_Y(y), m_Shape(pMap->getLayout().size.x, 6) {
		Hex h = getHex();
		HexMapLayout l = pMap->getLayout();
		sf::Vector2f center = Hex::hex_to_pixel(h, l);

		m_Shape.setFillColor(sf::Color::Green);
		m_Shape.setPosition(center - l.size);
	}

	Tile::~Tile() { }

	int Tile::getX() const {
		return m_X;
	}

	int Tile::getY() const {
		return m_Y;
	}

	void Tile::draw(sf::RenderWindow& window) const {
		window.draw(m_Shape);
	}

	Hex Tile::getHex() const {
		return Hex::even_r_to_cube(sf::Vector2i(m_X, m_Y));
	}

	sf::Texture Tile::getTexture() const {
		return m_Texture;
	}
}