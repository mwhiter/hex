#pragma once

#include <iostream>

namespace mandr {
	struct Point {
		Point() : x(0.0f), y(0.0f) {}
		Point(float x, float y) : x(x), y(y) {}
		float x;
		float y;
	};
}

std::ostream& operator<<(std::ostream& os, mandr::Point& p);