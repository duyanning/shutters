#include "wincpp.hpp"
#include "nurserWindow.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

HWND
ShuttersImpl::getNurserWindow()
{
	static HWND hwndNurser;
	if (!hwndNurser) {
		hwndNurser = createNurserWindow();
	}

	return hwndNurser;
}

HWND
ShuttersImpl::createNurserWindow()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof (WNDCLASSEX); 

	wcex.style			= 0;
	wcex.lpfnWndProc	= (WNDPROC)nurserWindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= GetModuleHandle(NULL);
	wcex.hIcon			= 0;
	wcex.hCursor		= 0;
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= L"ShuttersNurserClass";
	wcex.hIconSm		= 0;

	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindow(
			L"ShuttersNurserClass",
			L"",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			0,
			CW_USEDEFAULT,
			0,
			NULL,
			NULL,
			GetModuleHandle(NULL),
			NULL
		);

	return hWnd;

}

LRESULT CALLBACK
ShuttersImpl::nurserWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_COMMAND:
	{
		HWND hwndCtl = HWND(lParam);

		// If notification is from a control and the control is no longer this
		//   window's child, pass it on to the new parent.
		if (hwndCtl && !::IsChild(hWnd, hwndCtl))
			return ::SendMessage(::GetParent(hwndCtl), WM_COMMAND, wParam,  lParam);
	}
		break;
	//case WM_TIMER:
	//{
	//}
	//	break;
	default:
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
