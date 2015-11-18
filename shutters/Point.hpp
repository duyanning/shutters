#pragma once

namespace Shutters {

class Point {
public:
	Point(int x = 0, int y = 0);
	int x;
	int y;
};

inline
Point::Point(int x1, int y1)
:
	x(x1),
	y(y1)
{
}

inline bool operator==(const Point& pt1, const Point& pt2)
{
	return (pt1.x == pt2.x) && (pt1.y == pt2.y);
}

}
