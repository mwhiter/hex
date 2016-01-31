#pragma once

#include "Hex.h"
#include "Infos.h"

namespace mandr {

	class Tile
	{
	public:
		Tile(HexMap* pMap, TerrainInfo* pTerrain, int x, int y);
		~Tile();

		int getX() const;
		int getY() const;

		void draw(sf::RenderWindow& window) const;

		TerrainInfo* getTerrain() const;

		void changeTerrain(TerrainInfo* pNewTerrain);

		Hex getHex() const;
	private:
		int m_X, m_Y;	// even_r coordinates on hex grid

		HexMap* m_pMap;
		TerrainInfo* m_pTerrainInfo;
		sf::Texture* m_pSelectTexture;

		sf::Sprite m_Sprite;
		sf::Sprite m_SelectSprite;
	};

}