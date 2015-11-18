#pragma once

#include "Point.hpp"
#include "Size.hpp"

namespace Shutters {

class Rectangle {
public:
	Rectangle(int x = 0, int y = 0, int width = 1, int height = 1);
	Rectangle(Point location, Size size);
	int left() const;
	int top() const;
	int right() const;
	int bottom() const;

	int x() const;
	void setX(int x);
	int y() const;
	void setY(int y);
	int width() const;
	void setWidth(int width);
	int height() const;
	void setHeight(int height);
	Point location() const;
	void setLocation(Point location);
	Size size() const;
	void setSize(Size size);
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};
//
//inline
//Point::Point(int x1, int y1)
//:
//	x(x1),
//	y(y1)
//{
//}

}
