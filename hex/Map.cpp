#include "Map.h"
#include <iostream>
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
		m_Layout(layout), m_Width(width), m_Height(height), m_Vertices(sf::PrimitiveType::Lines, width * height * 12)
	{
		// Initialize the hex map with axial coordinates in even-r
		for (int r = 0; r < height; r++) {
			int r_offset = floor((r+1)/2);
			for (int q = -r_offset; q < width - r_offset; q++) {
				Hex hex(q, r, -q-r);
				sf::Vector2i even_r = Hex::cube_to_even_r(hex);
				m_Grid.insert(std::pair<Hex, Tile*>(hex, new Tile(even_r.x, even_r.y)));

				// Load graphical information for hex
				sf::Vertex* hex_verts = &m_Vertices[(even_r.x + even_r.y * m_Width) * 12];
				std::vector<sf::Vector2f> corners = hex.polygon_corners(m_Layout);

				hex_verts[0].position = corners[0];
				hex_verts[1].position = corners[1];
				hex_verts[2].position = corners[1];
				hex_verts[3].position = corners[2];
				hex_verts[4].position = corners[2];
				hex_verts[5].position = corners[3];
				hex_verts[6].position = corners[3];
				hex_verts[7].position = corners[4];
				hex_verts[8].position = corners[4];
				hex_verts[9].position = corners[5];
				hex_verts[10].position = corners[5];
				hex_verts[11].position = corners[0];
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
				if (pTile != nullptr) {
					result.push_back(pTile);
				}
			}
		}

		return result;
	}

	void HexMap::draw(sf::RenderWindow& window) const {
		window.draw(m_Vertices);
	}

	Tile* HexMap::getTile(int q, int r, int s) const {
		return getTile(Hex(q, r, s));
	}

	Tile* HexMap::getTile(Hex& h) const {
		std::unordered_map<Hex, Tile*>::const_iterator it = m_Grid.find(h);

		if (it == m_Grid.end()) return nullptr;
		else return it->second;
	}
	const HexMapLayout HexMap::getLayout() const
	{
		return m_Layout;
	}
}