#pragma once

#include "Hex.h"

namespace mandr {

	class Tile
	{
	public:
		Tile(int x, int y);
		~Tile();

		Hex getHex() const;
	private:
		int x, y;	// even_r coordinates on hex grid
	};

}