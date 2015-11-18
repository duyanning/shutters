#include "wincpp.hpp"

#include "Button.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"
#include "EventArgs.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

Button::Button(const wstring& text)
{
	ShuttersImpl::modifyStyle(handle(), 0, BS_PUSHBUTTON);
}

Button::~Button()
{
}
