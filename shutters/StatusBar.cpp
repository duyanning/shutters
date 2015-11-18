#include "wincpp.hpp"
#include "StatusBar.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

StatusBar::StatusBar()
{
	using namespace ShuttersImpl;

	INITCOMMONCONTROLSEX initCtrls;
	initCtrls.dwSize = sizeof initCtrls;
	initCtrls.dwICC = ICC_BAR_CLASSES;
	BOOL b = ::InitCommonControlsEx(&initCtrls);

	HWND handle = ::CreateWindowEx(
			0,
			STATUSCLASSNAME,
			0,
			WS_CHILD | WS_VISIBLE,
			0,
			0,
			0,
			0,
			getNurserWindow(),
			0,
			0,
			NULL
		);
	setOldWndProc(replaceWndProc(handle, S_WndProc));
	setHandle(handle);
	addToMap(handle);
}

StatusBar::~StatusBar()
{
}
