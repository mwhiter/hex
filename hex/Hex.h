#pragma once

#include "Point.h"
#include <SFML/Graphics.hpp>

namespace mandr {
	class Hex
	{
	public:
		friend class Map;
		friend std::ostream& operator<<(std::ostream& os, Hex h);

		Hex(int q, int r);			// Axial

		~Hex();

		inline int getCol() const { return q; }
		inline int getRow() const { return r; }

		static sf::Vector3i toCube(Hex& h);
		static int cube_distance(sf::Vector3i a, sf::Vector3i b);
		static int distance(Hex& a, Hex& b);

		void draw(sf::RenderWindow& window);
	private:
		int q, r;		// axial

		float size;
		float width, height;
	};
}



