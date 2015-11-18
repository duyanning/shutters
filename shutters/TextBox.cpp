#include "wincpp.hpp"
#include "TextBox.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"
#include "EventArgs.hpp"
#include "Rectangle.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

TextBox::TextBox()
:
	m_multiline(false)
{
	using namespace ShuttersImpl;

	HWND handle = createNativeControl(m_multiline);
	setOldWndProc(replaceWndProc(handle, S_WndProc));
	setHandle(handle);
	addToMap(handle);
}

TextBox::~TextBox()
{
}

HWND
TextBox::createNativeControl(bool multiline)
{
	DWORD dwStyle = (WS_CHILD | WS_VISIBLE);
	if (multiline) {
		dwStyle |= ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN;
	}
	else {
		dwStyle |= ES_AUTOHSCROLL;
	}

	HWND handle = ::CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"edit",
			L"",
			dwStyle,
			CW_USEDEFAULT,
			0,
			CW_USEDEFAULT,
			0,
			ShuttersImpl::getNurserWindow(),
			0,
			0,
			NULL
		);

	return handle;

}

bool
TextBox::multiline()
{
	return true;
}

void
TextBox::setMultiline(bool b)
{
	using namespace ShuttersImpl;
	//if (b) {
	//	ShuttersImpl::modifyStyle(handle(),
	//		ES_AUTOHSCROLL,
	//		ES_MULTILINE | ES_AUTOVSCROLL |ES_WANTRETURN);
	//}
	//else {
	//	ShuttersImpl::modifyStyle(handle(),
	//		ES_MULTILINE | ES_AUTOVSCROLL |ES_WANTRETURN,
	//		ES_AUTOHSCROLL);
	//}

	if (m_multiline == b)  return;
	m_multiline = b;

	/*
	some styles cannot be changed after creation,
	so we MUST destroy old EDIT and create a new one with these styles.
	*/

	// 1. create new one
	HWND newHandle = createNativeControl(m_multiline);

	// 2. save properties
	Rectangle oldBounds = bounds();
	bool oldVisible = visible();

	// 3. replace old one with new one
	HWND oldHandle = handle();
	// let oldHandle's parent be newHandle's parent
	::SetParent(newHandle, ::GetParent(oldHandle));
	// let oldHandle's children be newHandle's children
	// ... not implemented.

	// 4. destroy old one
	removeFromMap(destroyHandle());

	// 5. install new one
	setOldWndProc(replaceWndProc(newHandle, S_WndProc));
	setHandle(newHandle);
	addToMap(newHandle);

	// 6. restore properties
	setBounds(oldBounds);
	setVisible(oldVisible);
}
