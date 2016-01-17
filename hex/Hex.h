#pragma once

#include <SFML/Graphics.hpp>
#include "enums.h"
#include <cassert>
#include <cmath>


namespace mandr {
	// Forward declarations
	struct HexMapLayout;

	struct Hex
	{
		int q;
		int r;
		int s;

		friend class HexMap;
		friend std::ostream& operator<<(std::ostream& os, Hex h);

		static const Hex neighbors[NUM_DIRECTIONS];

		Hex(int q, int r) : q(q), r(r), s(-q-r) {
			assert(q + r + s == 0);
		};

		Hex(int q, int r, int s) : q(q), r(r), s(s) {
			assert(q + r + s == 0);
		};

		friend bool operator==(const Hex& a, const Hex& b);
		friend Hex operator+(const Hex& a, const Hex& b);
		Hex& operator+=(const Hex& other);
		friend Hex operator-(const Hex& a, const Hex& b);
		Hex& operator-=(const Hex& other);
		friend Hex operator*(const Hex& a, int k);
		Hex& operator*=(int k);

		static int length(const Hex& a);
		static int distance(const Hex& a, const Hex& b);

		Hex getAdjacent(const Hex& h, DirectionType direction) const;

		// Static methods
		static Hex even_r_to_cube(const sf::Vector2i& v);
		static sf::Vector2i cube_to_even_r(const Hex& a);
		static Hex round(float x, float y, float z);

		void draw(const HexMapLayout& layout, sf::RenderWindow& window) const;

		static sf::Vector2f hex_to_pixel(const Hex& h, const HexMapLayout& layout);
		static Hex pixel_to_hex(const HexMapLayout& layout, sf::Vector2f& p);

		sf::Vector2f corner_offset(const HexMapLayout& layout, int corner) const;
		std::vector<sf::Vector2f> polygon_corners(const HexMapLayout& layout) const;
	};
}

// Hash for Hex - because unordered map does not come default with one
template <> struct std::hash<mandr::Hex> {
	size_t operator()(const mandr::Hex& h) const {
		std::hash<int> int_hash;
		size_t hq = int_hash(h.q);
		size_t hr = int_hash(h.r);
		return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
	}
};


