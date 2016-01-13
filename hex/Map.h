#pragma once

#include "Hex.h"
#include "Tile.h"
#include <unordered_map>

namespace mandr {
	struct HexMapOrientation {
		const double f0, f1, f2, f3;	// 2x2 forward matrix
		const double b0, b1, b2, b3;	// 2x2 inverse matrix
		const double start_angle;

		HexMapOrientation(double f0, double f1, double f2, double f3,
			double b0, double b1, double b2, double b3,
			double start_angle) :
			f0(f0), f1(f1), f2(f2), f3(f3),
			b0(b0), b1(b1), b2(b2), b3(b3),
			start_angle(start_angle) {}
	};

	struct HexMapLayout {
		const HexMapOrientation orientation;
		const sf::Vector2f size;
		const sf::Vector2f origin;
		HexMapLayout(HexMapOrientation orientation, sf::Vector2f size, sf::Vector2f origin) :
			orientation(orientation), size(size), origin(origin) {}
	};

	class HexMap
	{
	public:

		const static HexMapOrientation Orientation_Horizontal;
		const static HexMapOrientation Orientation_Vertical;

		HexMap(const HexMapLayout& layout, int width, int height);
		~HexMap();

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }

		std::vector<Tile*> getTilesInRange(Hex& hex, int range) const;

		void draw(sf::RenderWindow& window) const;

		Tile* getTile(int q, int r, int s) const;
		Tile* getTile(Hex& h) const;

		const HexMapLayout getLayout() const;
	private:
		std::unordered_map<Hex, Tile*> m_Grid;
		const HexMapLayout m_Layout;
		int m_Width;
		int m_Height;
	};

}