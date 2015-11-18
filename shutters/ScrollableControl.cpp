#include "wincpp.hpp"
#include "ScrollableControl.hpp"
#include "Rectangle.hpp"

namespace Shutters {

ScrollableControl::ScrollableControl()
:
	m_autoScroll(false),
	m_autoScrollPosition(0, 0),
	//m_xMinPos(0),
	//m_xMaxPos(0),
	//m_yMinPos(0),
	//m_yMaxPos(0),
	m_displayRectangle(0, 0, 0, 0)
{
}

void
ScrollableControl::setAutoScroll(bool autoScroll)
{
	if (m_autoScroll)  return;

	m_autoScroll = autoScroll;
}

bool
ScrollableControl::autoScroll()
{
	return m_autoScroll;
}

Point
ScrollableControl::autoScrollPosition()
{
	return Point(-m_autoScrollPosition.x, -m_autoScrollPosition.y);
}

void
ScrollableControl::setAutoScrollPosition(Point point)
{
	int deltaX = m_autoScrollPosition.x - point.x;
	int deltaY = m_autoScrollPosition.y - point.y;

	m_autoScrollPosition = point;

	for (HWND hChild = ::GetWindow(handle(), GW_CHILD); hChild != NULL; hChild = ::GetWindow(hChild, GW_HWNDNEXT)) {
		Window* control = S_HandleToPointer(hChild);
		if (control) {
			control->setLocation(
					control->location().x + deltaX,
					control->location().y + deltaY
				);
		}
	}

	adjustScrollBar();
}

void
ScrollableControl::setAutoScrollMinSize(Size size)
{
	m_autoScrollMinSize = size;
}

Size
ScrollableControl::autoScrollMinSize()
{
	return m_autoScrollMinSize;
}

void
ScrollableControl::onControlAdded(ControlEventArgs& e)
{
	//Base::onControlAdded(e);
	Window* control = e.control;
	Rectangle rect = control->bounds();

	if (rect.left() < m_displayRectangle.left())
		m_displayRectangle.setX(rect.left());
	if (rect.top() < m_displayRectangle.top())
		m_displayRectangle.setY(rect.top());
	if (rect.right() > m_displayRectangle.right())
		m_displayRectangle.setWidth(rect.right() - m_displayRectangle.left());
	if (rect.bottom() > m_displayRectangle.bottom())
		m_displayRectangle.setHeight(rect.bottom() - m_displayRectangle.top());

	adjustScrollBar();
}

void
ScrollableControl::onControlRemoved(ControlEventArgs& e)
{
	//Base::onControlRemoved(e);
	adjustScrollBar();
}


void
ScrollableControl::wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result)
{
	switch (message) {
	case WM_HSCROLL:
	{
		//Point autoScrollPos = m_autoScrollPosition;
		int delta;
		int nCode = (int) LOWORD(wParam);  // scroll bar value 
		int nPos = (short int) HIWORD(wParam);   // scroll box position 

		switch (nCode) {
		case SB_LINELEFT:
			delta = -10;
			break;
		case SB_PAGELEFT:
			break;
		case SB_THUMBTRACK:
			delta = nPos - m_autoScrollPosition.x;
			break;
		case SB_PAGERIGHT:
			break;
		case SB_LINERIGHT:
			delta = 10;
			break;
		default:
			goto end;
		}

		int scrollPos = m_autoScrollPosition.x + delta;
		int maxPos = 1000;

		if (scrollPos < 0)
			delta = -m_autoScrollPosition.x;
		else if (scrollPos > maxPos)
			delta = maxPos - m_autoScrollPosition.x;

		if (delta != 0) {
			Point autoScrollPos = m_autoScrollPosition;
			autoScrollPos.x += delta;
			setAutoScrollPosition(autoScrollPos);
		}

		processed = true;
	}
		break;
	case WM_VSCROLL:
	{
		processed = true;
	}
		break;
	case WM_SIZE:
	{
		int nWidth = LOWORD(lParam);  // width of client area 
		int nHeight = HIWORD(lParam); // height of client area 
		if (m_displayRectangle.width() == 0) {
			m_displayRectangle.setSize(Size(nWidth, nHeight));
		}

		processed = true;
	}
		break;
	default:
		break;
	}

end:

	Base::wndProc(message, wParam, lParam, processed, result);
}

void
ScrollableControl::adjustScrollBar()
{
	::SetScrollRange(handle(), SB_HORZ, 0, m_displayRectangle.width() - 1, TRUE);
	::SetScrollPos(handle(), SB_HORZ, m_autoScrollPosition.x, TRUE);

	::SetScrollRange(handle(), SB_VERT, 0, m_displayRectangle.height(), TRUE);
	::SetScrollPos(handle(), SB_VERT, m_autoScrollPosition.y, TRUE);
}

Rectangle
ScrollableControl::displayRectangle() const
{
	return m_displayRectangle;
}

void
ScrollableControl::scrollControlIntoView(Window* activeControl)
{
	if (!autoScroll())  return;
	if (!hScroll() && !vScroll())  return;
}

void
ScrollableControl::setHScroll(bool hScroll)
{
	// not implemented
}

bool
ScrollableControl::hScroll()
{
	// not implemented
	return true;
}

void
ScrollableControl::setVScroll(bool vScroll)
{
	// not implemented
}

bool
ScrollableControl::vScroll()
{
	// not implemented
	return true;
}

}
