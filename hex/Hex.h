#pragma once

#include <SFML/Graphics.hpp>
#include "enums.h"

namespace mandr {
	// Forward declarations
	struct HexMapLayout;

	class Hex
	{
	public:

		struct Coordinates {
			Coordinates(int q, int r) : q(q), r(r) {}
			int q;
			int r;

			friend Coordinates operator+(const Coordinates& a, const Coordinates& b);
			Coordinates& operator+=(const Coordinates& other);
		};

		friend class HexMap;
		friend std::ostream& operator<<(std::ostream& os, Hex h);

		Hex(HexMap* pMap, int col, int row);

		~Hex();

		Hex* getAdjacent(DirectionType direction) const;

		// Cube coordinate accessors
		inline int c_q() { return m_Coords.q; }
		inline int c_r() { return m_Coords.r; }
		inline int c_s() { return -m_Coords.q - m_Coords.r; }

		inline Coordinates getCoords() const { return m_Coords; }
		inline int getCol() const { return m_Coords.q; }
		inline int getRow() const { return m_Coords.r; }

		// Static methods
		static sf::Vector3i even_r_to_cube(const Coordinates& c);
		static sf::Vector3i even_r_to_cube(int q, int r);
		static Coordinates cube_to_even_r(int x, int y, int z);
		static int distance(const Hex& a, const Hex& b);

		void draw(const HexMapLayout& layout, sf::Window& window) const;
	private:
		sf::Vector2i hex_to_pixel(const HexMapLayout& layout);
		Hex::Coordinates pixel_to_hex(const HexMapLayout& layout, sf::Vector2i& p);

		static Hex::Coordinates cube_round(double x, double y, double z);
		static int cube_distance(sf::Vector3i a, sf::Vector3i b);

		HexMap* m_pMap;
		Coordinates m_Coords; // offset coordinates
	};
}



