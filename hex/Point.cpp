#include "PCH.h"
#include "Point.h"

std::ostream& operator<<(std::ostream& os, mandr::Point& p) {
	os << "{ " << p.x << ", " << p.y << " }";
	return os;
}