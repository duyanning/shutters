#pragma once

#include "RootWindow.hpp"

namespace Shutters {

	class EventArgs;

	class FrameWindow : public RootWindow {
		typedef RootWindow Base;
	public:
//		FrameWindow(RootWindow* owner = 0);
		FrameWindow();
		~FrameWindow();
	protected:
	//	virtual void wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result);
	private:
	};

}
