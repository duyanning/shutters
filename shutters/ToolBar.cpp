#include "wincpp.hpp"
#include "ToolBar.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"


#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

ToolBar::ToolBar()
{
	using namespace ShuttersImpl;

	INITCOMMONCONTROLSEX initCtrls;
	initCtrls.dwSize = sizeof initCtrls;
	initCtrls.dwICC = ICC_BAR_CLASSES;
	BOOL b = ::InitCommonControlsEx(&initCtrls);

	HWND handle = ::CreateWindowEx(
			0,
			TOOLBARCLASSNAME,
			0,
			WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE,
			0,
			0,
			0,
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

ToolBar::~ToolBar()
{
}

void
ToolBar::add(const wstring& t)
{
	wchar_t szBuf[8] = L"CHANGE";
	//LPTSTR pszBuf;
	TBBUTTONINFO tbi;
	LPTBBUTTONINFO lptbbi;

	// Other code here.
	// Initialize pszBuf and lptbbi.

	// These are the only fields of the TBBUTTONINFO structure that 
	// need to be changed to modify text.   
	tbi.dwMask = TBIF_TEXT;
	tbi.cbSize = sizeof (TBBUTTONINFO);
	tbi.pszText = szBuf;
	tbi.cchText = sizeof (szBuf);
	::SendMessage(handle(), TB_SETBUTTONINFO, 2, (LPARAM)
		(LPTBBUTTONINFO)&tbi);
}

void
ToolBar::add(ToolBarButton& btn)
{
}

//===========================================

void
ToolBarButton::setText(const wstring& t)
{
	m_text = t;
}
