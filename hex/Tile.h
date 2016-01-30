#pragma once

#include "Hex.h"

namespace mandr {

	class Tile
	{
	public:
		Tile(HexMap* pMap, TerrainType type, int x, int y);
		~Tile();

		int getX() const;
		int getY() const;

		void draw(sf::RenderWindow& window) const;

		TerrainType getTerrain() const;

		Hex getHex() const;
		sf::Texture getTexture() const;
	private:
		int m_X, m_Y;	// even_r coordinates on hex grid

		TerrainType m_Terrain;

		HexMap* m_pMap;

		sf::Texture m_SelectTexture;
		sf::Texture m_Texture;
		sf::Sprite m_Sprite;
		sf::Sprite m_SelectSprite;
	};

}