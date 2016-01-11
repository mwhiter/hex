#pragma once

#include "Hex.h"

namespace mandr {
	typedef std::pair<int, int> hex_coord;

	class Map
	{
	public:
		struct Orientation {
			const double f0, f1, f2, f3;	// 2x2 forward matrix
			const double b0, b1, b2, b3;	// 2x2 inverse matrix
			const double start_angle;

			Orientation(double f0, double f1, double f2, double f3,
				double b0, double b1, double b2, double b3,
				double start_angle) :
				f0(f0), f1(f1), f2(f2), f3(f3),
				b0(b0), b1(b1), b2(b2), b3(b3),
				start_angle(start_angle) {}
		};

		const static Orientation Orientation_Horizontal;

		Map(int width, int height);
		~Map();

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }

		std::vector<Hex*> getHexesInRange(Hex::Coordinates& coords, int range) const;
		std::vector<Hex*> getHexesInRange(Hex& hex, int range) const;

		Hex* getHex(int q, int r) const;
		Hex* getHex(Hex::Coordinates& c) const;
	private:
		std::map<hex_coord, Hex*> m_Grid;
		int m_Width;
		int m_Height;
	};

}