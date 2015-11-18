#include "wincpp.hpp"
#include "NativeComboBoxCreator.hpp"

using namespace ShuttersImpl;

HWND
NativeComboBoxCreator::create()
{
	return 0;
}

NativeWindowCreator& getNativeComboBoxCreator()
{
	static NativeComboBoxCreator creator;
	return creator;
}
