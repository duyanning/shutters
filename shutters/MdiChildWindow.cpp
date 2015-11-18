#include "wincpp.hpp"
#include "MdiChildWindow.hpp"
#include "MdiFrameWindow.hpp"
#include "MenuBar.hpp"
#include "CommandItem.hpp"


#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

MdiChildWindow::MdiChildWindow(MdiFrameWindow* mdiFrame)
:
	m_mdiFrame(mdiFrame)
{
	HWND handle = mdiFrame->createChild();
	setHandle(handle);
	addToMap(handle);
}

MdiChildWindow::~MdiChildWindow()
{
}

void
MdiChildWindow::onActivate(bool)
{
}

void
MdiChildWindow::wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result)
{
	if (message == WM_SYSCOMMAND) {
		int x = 0;
		x++;
	}

	switch (message)
	{
	case WM_QUERYENDSESSION:
	case WM_CLOSE:
		getMdiFrame()->deleteChild(this);
		processed = true;
		break;
	case WM_MDIACTIVATE:
		onActivate(lParam == (LPARAM)handle());
		processed = true;
		break;
	case WM_NCDESTROY:
		delete this;
		processed = true;
		break;
	default:
		break;
	}

	Base::wndProc(message, wParam, lParam, processed, result);
}

MdiFrameWindow*
MdiChildWindow::getMdiFrame()
{
	return m_mdiFrame;
}
