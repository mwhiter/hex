#pragma once
class Tile
{
public:
	Tile(int x, int y);
	~Tile();

private:
	int x, y;	// even_r coordinates on hex grid
};

