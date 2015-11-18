#include "wincpp.hpp"
#include "Shutters.hpp"
#include "RootWindow.hpp"
#include "Form.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

namespace Shutters {

	void startupWnd_closed(void*, EventArgs&)
	{
		::PostQuitMessage(0);
	}

	void SetStartupWindow(RootWindow& startupWnd)
	{
		SetStartupWindow(&startupWnd);
	}

	void SetStartupWindow(RootWindow* startupWnd)
	{
		startupWnd->closed.addListener(startupWnd_closed);
	}

	void SetStartupWindow(Form& startupWnd)
	{
		SetStartupWindow(&startupWnd);
	}

	void SetStartupWindow(Form* startupWnd)
	{
		startupWnd->closed.addListener(startupWnd_closed);
	}

}

#pragma comment(lib, "comctl32.lib")
