#include "wincpp.hpp"
#include "NativeTextBoxCreator.hpp"
#include "nurserWindow.hpp"

namespace ShuttersImpl {

HWND
NativeTextBoxCreator::create()
{
	return 0;
}

NativeWindowCreator& getNativeTextBoxCreator()
{
	static NativeTextBoxCreator creator;
	return creator;
}

}
