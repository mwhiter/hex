#pragma once

#include "Hex.h"

namespace mandr {
	typedef std::pair<int, int> hex_coord;

	class Map
	{
	public:
		Map(int width, int height);
		~Map();

		Hex* getHex(int q, int r);
	private:
		std::map<hex_coord, Hex*> grid;
		int width;
		int height;
	};

}