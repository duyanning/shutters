#include "wincpp.hpp"

#include "ChildWindow.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

ChildWindow::ChildWindow()
{
}

ChildWindow::~ChildWindow()
{
}

Window*
ChildWindow::getParent()
{
	HWND hParent = ::GetParent(handle());
	Window* parent = S_HandleToPointer(hParent);
	return parent;
}
