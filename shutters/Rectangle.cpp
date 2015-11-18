#include "wincpp.hpp"
#include "Rectangle.hpp"

namespace Shutters {

Rectangle::Rectangle(int x, int y, int width, int height)
:
	m_x(x),
	m_y(y),
	m_width(width),
	m_height(height)
{
}

Rectangle::Rectangle(Point location, Size size)
:
	m_x(location.x),
	m_y(location.y),
	m_width(size.width),
	m_height(size.height)
{
}

int
Rectangle::left() const  {	return x(); }

int
Rectangle::top() const  { return y(); }

int
Rectangle::right() const  { return x() + width(); }

int
Rectangle::bottom() const  { return y() + height(); }


int
Rectangle::x() const  { return m_x; }

void
Rectangle::setX(int x)  { m_x = x; }

int
Rectangle::y() const  { return m_y; }

void
Rectangle::setY(int y)  { m_y = y; }

int
Rectangle::width() const  { return m_width; }

void
Rectangle::setWidth(int width)  { m_width = width; }

int
Rectangle::height() const  { return m_height; }

void
Rectangle::setHeight(int height)  { m_height = height; }

Point
Rectangle::location() const { return Point(m_x, m_y); }

void
Rectangle::setLocation(Point location)  { m_x = location.x;	m_y = location.y; }

Size
Rectangle::size() const {	return Size(m_width, m_height); }

void
Rectangle::setSize(Size size) { m_width= size.width; m_height = size.height; }

}
