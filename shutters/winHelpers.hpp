#pragma once


namespace ShuttersImpl {

	WNDPROC replaceWndProc(HWND handle, WNDPROC newProc);
	bool modifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	bool modifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);

}
