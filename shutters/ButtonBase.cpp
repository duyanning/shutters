#include "wincpp.hpp"
#include "ButtonBase.hpp"
#include "EventArgs.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"

using namespace Shutters;

ButtonBase::ButtonBase(const wstring& text)
{
	using namespace ShuttersImpl;

	HWND handle = ::CreateWindowEx(
			0,
			L"BUTTON",
			text.c_str(),
			WS_CHILD | WS_VISIBLE,
			CW_USEDEFAULT,
			0,
			CW_USEDEFAULT,
			0,
			getNurserWindow(),
			0,
			0,
			NULL
		);

	setOldWndProc(replaceWndProc(handle, S_WndProc));
	setHandle(handle);
	addToMap(handle);
}

ButtonBase::~ButtonBase()
{
}

void
ButtonBase::onClicked(EventArgs& e)
{
	click.fire(this, e);
}
