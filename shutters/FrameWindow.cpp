#include "wincpp.hpp"
#include "FrameWindow.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

//FrameWindow::FrameWindow(RootWindow* owner)
FrameWindow::FrameWindow()
//:
//	Base(owner)
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
//			owner ? owner->handle() : 0,
			0,
			0,
			::GetModuleHandle(0),
			0
		);

	setHandle(handle);
	addToMap(handle);
}

FrameWindow::~FrameWindow()
{
}
