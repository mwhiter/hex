#pragma once

#include "Hex.h"

namespace mandr {

	class Tile
	{
	public:
		Tile(int x, int y);
		~Tile();

		int getX() const;
		int getY() const;

		Hex getHex() const;
	private:
		int m_X, m_Y;	// even_r coordinates on hex grid
	};

}