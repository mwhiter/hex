#pragma once

#include "Hex.h"

namespace mandr {

	class Tile
	{
	public:
		Tile(HexMap* pMap, int x, int y);
		~Tile();

		int getX() const;
		int getY() const;

		void draw(sf::RenderWindow& window) const;

		Hex getHex() const;
		sf::Texture getTexture() const;
	private:
		int m_X, m_Y;	// even_r coordinates on hex grid

		HexMap* pMap;

		sf::Texture m_Texture;
		sf::Sprite m_Sprite;
	};

}