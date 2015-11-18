#include "wincpp.hpp"
#include "NativeListBoxCreator.hpp"

namespace ShuttersImpl {

HWND
NativeListBoxCreator::create()
{
	return 0;
}

NativeWindowCreator& getNativeListBoxCreator()
{
	static NativeListBoxCreator creator;
	return creator;
}

}
