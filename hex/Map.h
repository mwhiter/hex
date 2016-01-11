#pragma once

#include "Hex.h"

namespace mandr {

	class Map
	{
	public:
		Map(int width, int height);
		~Map();

		Hex* getHex(int r, int q);
	private:
		std::vector<std::vector<Hex*>> grid;
		int width;
		int height;
	};

}