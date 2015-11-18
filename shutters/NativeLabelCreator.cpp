#include "wincpp.hpp"
#include "NativeLabelCreator.hpp"
#include "nurserWindow.hpp"

namespace ShuttersImpl {

HWND
NativeLabelCreator::create()
{
	return 0;
}

NativeWindowCreator& getNativeLabelCreator()
{
	static NativeLabelCreator creator;
	return creator;
}

}
