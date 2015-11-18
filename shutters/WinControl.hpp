#pragma once

#include "ChildWindow.hpp"

namespace Shutters {

class WinControl : public ChildWindow {
	typedef ChildWindow Base;
public:
	WinControl();
	~WinControl();
protected:
	void wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result);

	void setOldWndProc(WNDPROC oldWndProc);
	void callOldWndProc();

	void onMouseDown(MouseEventArgs& e);
	void onMouseUp(MouseEventArgs& e);
	void onMouseMove(MouseEventArgs& e);

	virtual void onReflected();

private:
	WNDPROC m_oldWndProc;
};

}
