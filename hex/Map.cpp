#include "Map.h"

namespace mandr {
	const Map::Orientation Map::Orientation_Horizontal = Map::Orientation(	sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
															sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0, 
															0.5);

	Map::Map(int width, int height) :
		m_Width(width), m_Height(height)
	{
		// Initialize the hex map with axial coordinates
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				m_Grid.insert(std::pair<hex_coord, Hex*>(hex_coord(col, row), new Hex(this, col, row)));
			}
		}
	}

	Map::~Map()
	{
	}

	// Get all hexes in range of the hex
	std::vector<Hex*> Map::getHexesInRange(Hex::Coordinates& coords, int range) const {
		std::vector<Hex*> result;

		// should put an assert here
		if (range <= 0) return result;

		for (int dx = -range; dx <= range; dx++) {
			for (int dy = std::max(-range, -dx - range); dy <= std::min(range, -dx + range); dy++) {
				int dz = -dx - dy;
				Hex* pHex = getHex(coords + Hex::cube_to_even_r(dx, dy, dz));
				if (pHex != NULL) {
					result.push_back(pHex);
				}
			}
		}

		return result;
	}

	// Get all hexes in range of the hex
	std::vector<Hex*> Map::getHexesInRange(Hex& hex, int range) const {
		return getHexesInRange(hex.getCoords(), range);
	}

	Hex* Map::getHex(int q, int r) const {
		std::map<hex_coord, Hex*>::const_iterator it = m_Grid.find(hex_coord(q, r));
		
		if (it == m_Grid.end()) return NULL;
		else return it->second;
	}

	Hex* Map::getHex(Hex::Coordinates& c) const {
		return getHex(c.q, c.r);
	}
}