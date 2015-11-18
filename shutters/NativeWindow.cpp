#include "wincpp.hpp"
#include "NativeWindow.hpp"


#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

NativeWindow::NativeWindow()
{
	HWND handle = S_CreateWindow(
			0,
			L"ShuttersClass",
			L"",
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			::GetModuleHandle(0),
			0
		);

	setHandle(handle);
	addToMap(handle);
}

NativeWindow::~NativeWindow()
{
}
