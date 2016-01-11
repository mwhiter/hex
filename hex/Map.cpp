#include "Map.h"

namespace mandr {

	Map::Map(int width, int height) :
		width(height * (width + height / 2)), height(height)
	{
		for (int r = 0; r < height; r++) {
			std::vector<Hex*> row;
			int offset = -(height / 2 - 1);
			for (int q = offset; q < width; q++) {
				// we need to check if this is actually a valid cell - if not, push NULL back into the array (to prevent negative indexing)
				int x = q + r / 2;
				if (x < 0 || x >= width) {
					std::cout << "deny (" << q << "," << r << ") because x is " << x << std::endl;
					row.push_back(NULL);
				}
				else
					row.push_back(new Hex(q, r));
			}
			grid.push_back(row);
		}
	}

	Map::~Map()
	{
	}

	Hex* Map::getHex(int r, int q) {
		if (r < 0 || r >= grid.size()) return NULL;
		if ((q + r / 2) >= grid[0].size()) return NULL;
		return grid[r][q + r / 2];
	}
}