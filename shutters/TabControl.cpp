#include "wincpp.hpp"
#include "TabControl.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"


#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

TabControl::TabControl()
{
	using namespace ShuttersImpl;

	HWND handle = ::CreateWindowEx(
			0,
			WC_TABCONTROL,
			L"",
			WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
			0,
			0,
			0,
			0,
			getNurserWindow(),
			NULL,
			0,
			NULL
		);
	setOldWndProc(replaceWndProc(handle, S_WndProc));
	setHandle(handle);
	addToMap(handle);
}

TabControl::~TabControl()
{
}

