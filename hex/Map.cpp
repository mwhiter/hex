#include "Map.h"

namespace mandr {

	Map::Map(int width, int height) :
		width(height * (width + height / 2)), height(height)
	{
		for (int r = 0; r < height; r++) {
			int offset = -(height / 2 - 1);
			for (int q = offset; q < width; q++) {
				grid.insert(std::pair<hex_coord, Hex*>(hex_coord(q, r), new Hex(this, q, r)));
			}
		}
	}

	Map::~Map()
	{
	}

	Hex* Map::getHex(int q, int r) {
		std::map<hex_coord, Hex*>::iterator it = grid.find(hex_coord(q,r));
		
		if (it == grid.end()) return NULL;
		else return it->second;
	}
}