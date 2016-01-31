#include "PCH.h"

namespace mandr {

	Tile::Tile(HexMap* pMap, TerrainInfo* terrain, int x, int y) : m_pMap(pMap), m_pTerrainInfo(terrain), m_X(x), m_Y(y) {
		Hex h = getHex();
		HexMapLayout l = m_pMap->getLayout();
		sf::Vector2f center = Hex::hex_to_pixel(h, l);

		// hard-coded, use some ui graphics definition
		m_pSelectTexture = Application::getInstance()->getTexture(2);

		//m_Sprite.scale(sf::Vector2f(2.0f,2.0f));

		m_Sprite.setTexture(*m_pTerrainInfo->getTexture());
		m_Sprite.setPosition(center - l.size);

		m_SelectSprite.setTexture(*m_pSelectTexture);
		m_SelectSprite.setPosition(center - l.size);
	}

	Tile::~Tile() { }

	TerrainInfo* Tile::getTerrain() const {
		return m_pTerrainInfo;
	}

	int Tile::getX() const {
		return m_X;
	}

	int Tile::getY() const {
		return m_Y;
	}
	
	void Tile::changeTerrain(TerrainInfo* pNewTerrain) {
		assert(pNewTerrain != NULL);
		assert(pNewTerrain->getTexture() != NULL);
		m_SelectSprite.setTexture(*pNewTerrain->getTexture());
	}

	void Tile::draw(sf::RenderWindow& window) const {
		window.draw(m_Sprite);

		// draw select sprite overlay if selected tile
		if (this == GAME.getSelectedTile())
			window.draw(m_SelectSprite);
	}

	Hex Tile::getHex() const {
		return Hex::even_r_to_cube(sf::Vector2i(m_X, m_Y));
	}
}