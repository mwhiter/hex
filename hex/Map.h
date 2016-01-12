#pragma once

#include "Hex.h"

namespace mandr {
	typedef std::pair<int, int> hex_coord;

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
		const HexMapOrientation o;
		const sf::Vector2f size;
		const sf::Vector2f origin;
		HexMapLayout(HexMapOrientation o, sf::Vector2f size, sf::Vector2f origin) :
			o(o), size(size), origin(origin) {}
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

		std::vector<Hex*> getHexesInRange(Hex::Coordinates& coords, int range) const;
		std::vector<Hex*> getHexesInRange(Hex& hex, int range) const;

		void draw(sf::Window& window) const;

		Hex* getHex(int q, int r) const;
		Hex* getHex(Hex::Coordinates& c) const;
	private:
		std::map<hex_coord, Hex*> m_Grid;
		const HexMapLayout m_Layout;
		int m_Width;
		int m_Height;
	};

}