#pragma once


namespace ShuttersImpl {

	HWND getNurserWindow();
	HWND createNurserWindow();
	LRESULT CALLBACK nurserWindowProc(HWND, UINT, WPARAM, LPARAM);

}
