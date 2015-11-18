#include "wincpp.hpp"
#include "NativeButtonCreator.hpp"
#include "nurserWindow.hpp"

namespace ShuttersImpl {

HWND
NativeButtonCreator::create()
{
	return 0;
}

NativeWindowCreator& getNativeButtonCreator()
{
	static NativeButtonCreator creator;
	return creator;
}

}
