#pragma once

#include "Hex.h"

namespace mandr {

	class Tile
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const Tile& tile);

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
		sf::CircleShape m_Shape;
	};

}