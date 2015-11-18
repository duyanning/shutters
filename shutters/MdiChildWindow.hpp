#pragma once

#include "ChildWindow.hpp"

namespace Shutters {

class MdiFrameWindow;

class MdiChildWindow : public ChildWindow {
	typedef ChildWindow Base;
	friend class MdiFrameWindow;
public:
	MdiChildWindow(MdiFrameWindow* mdiFrame);
	~MdiChildWindow();
	MdiFrameWindow* getMdiFrame();
protected:
	virtual void wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result);
	virtual void onActivate(bool b);

private:
	MdiFrameWindow* m_mdiFrame;
};

}