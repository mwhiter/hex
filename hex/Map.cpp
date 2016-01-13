#include "Map.h"

namespace mandr {
	const HexMapOrientation HexMap::Orientation_Horizontal
		= HexMapOrientation(sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
			sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0, 
			0.5);

	const HexMapOrientation HexMap::Orientation_Vertical
		= HexMapOrientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0),
			2.0 / 3.0, 0.0, -1.0 /3.0, sqrt(3.0) / 3.0,
			0.0);

	HexMap::HexMap(const HexMapLayout& layout, int width, int height) :
		m_Layout(layout), m_Width(width), m_Height(height)
	{
		// Initialize the hex map with axial coordinates
		for (int row = 0; row < height; row++) {
			int r_offset = (int)floor(row / 2);
			for (int col = -r_offset; col < width - r_offset; col++) {
				Hex hex(col, row);
				sf::Vector2i even_r = Hex::cube_to_even_r(hex);
				m_Grid.insert(std::pair<Hex, Tile*>(hex, new Tile(even_r.x, even_r.y)));
			}
		}
	}

	HexMap::~HexMap()
	{
	}

	std::vector<Tile*> HexMap::getTilesInRange(Hex& hex, int range) const {
		std::vector<Tile*> result;

		// should put an assert here
		if (range <= 0) return result;

		for (int dx = -range; dx <= range; dx++) {
			for (int dy = std::max(-range, -dx - range); dy <= std::min(range, -dx + range); dy++) {
				int dz = -dx - dy;
				Tile* pTile = getTile(hex + Hex(dx, dy, dz));
				if (pTile != NULL) {
					result.push_back(pTile);
				}
			}
		}

		return result;
	}

	void HexMap::draw(sf::RenderWindow& window) const {
		for (std::unordered_map<Hex, Tile*>::const_iterator it = m_Grid.begin(); it != m_Grid.end(); it++) {
			it->first.draw(m_Layout, window);
		}
	}

	Tile* HexMap::getTile(int q, int r, int s) const {
		return getTile(Hex(q, r, s));
	}

	Tile* HexMap::getTile(Hex& h) const {
		std::unordered_map<Hex, Tile*>::const_iterator it = m_Grid.find(h);

		if (it == m_Grid.end()) return NULL;
		else return it->second;
	}
	const HexMapLayout HexMap::getLayout() const
	{
		return m_Layout;
	}
}