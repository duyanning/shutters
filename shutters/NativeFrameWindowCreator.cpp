#include "wincpp.hpp"
#include "Window.hpp"
#include "NativeFrameWindowCreator.hpp"

namespace ShuttersImpl {

HWND
NativeFrameWindowCreator::create()
{
	return 0;
}

NativeWindowCreator& getFrameWindowCreator()
{
	static NativeFrameWindowCreator creator;
	return creator;
}

}
