#include "wincpp.hpp"
#include "TabPage.hpp"
#include "nurserWindow.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

namespace Shutters {

TabPage::TabPage()
{
	using namespace ShuttersImpl;

	HWND handle = S_CreateWindow(
			0,
			L"ShuttersClass",
			L"",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,
			CW_USEDEFAULT,
			0,
			CW_USEDEFAULT,
			0,
			getNurserWindow(),
			0,
			::GetModuleHandle(0),
			0
		);

	setHandle(handle);
	addToMap(handle);
}

}
