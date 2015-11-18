#include "wincpp.hpp"
#include "winHelpers.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

WNDPROC
ShuttersImpl::replaceWndProc(HWND handle, WNDPROC newProc)
{
	WNDPROC oldProc;

	oldProc = reinterpret_cast<WNDPROC>(
			::SetWindowLongPtr(handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(newProc))
		);

	return oldProc;
}

// Change a window's style
namespace {

bool _modifyStyle(HWND hWnd, int nStyleOffset,
	DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	LONG_PTR dwStyle = ::GetWindowLongPtr(hWnd, nStyleOffset);
	LONG_PTR dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
	if (dwStyle == dwNewStyle)
		return false;

	::SetWindowLongPtr(hWnd, nStyleOffset, dwNewStyle);
	if (nFlags != 0)
	{
		::SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
	}
	return true;
}

}

bool
ShuttersImpl::modifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	return _modifyStyle(hWnd, GWL_STYLE, dwRemove, dwAdd, nFlags);
}

bool
ShuttersImpl::modifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	return _modifyStyle(hWnd, GWL_EXSTYLE, dwRemove, dwAdd, nFlags);
}
