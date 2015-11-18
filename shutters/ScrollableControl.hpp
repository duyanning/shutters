#pragma once

#include "ChildWindow.hpp"
#include "Point.hpp"
#include "Size.hpp"
#include "Rectangle.hpp"

namespace Shutters {

	//class Rectangle;

	class ScrollableControl : public ChildWindow {
		typedef ChildWindow Base;
	public:
		ScrollableControl();
		// Properties
		void setAutoScroll(bool autoScroll);
		bool autoScroll();

		void setAutoScrollMargin(Size size);
		Size autoScrollMargin();

		void setAutoScrollMinSize(Size size);
		Size autoScrollMinSize();

		void setAutoScrollPosition(Point point);
		Point autoScrollPosition();

		Rectangle displayRectangle() const;

		void setHScroll(bool hScroll);
		bool hScroll();

		void setVScroll(bool vScroll);
		bool vScroll();

		void scrollControlIntoView(Window* activeControl);
		void setAutoScrollMargin(int x, int y);
	protected:
		void onControlAdded(ControlEventArgs& e);
		void onControlRemoved(ControlEventArgs& e);

		void wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result);
	private:
		void adjustScrollBar();
		bool m_autoScroll;
		Point m_autoScrollPosition;
		Size m_autoScrollMinSize;

		//int m_xMinPos, m_xMaxPos;
		//int m_yMinPos, m_yMaxPos;
		Rectangle m_displayRectangle;
	};

}
