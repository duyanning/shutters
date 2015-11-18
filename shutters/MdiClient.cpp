#include "wincpp.hpp"
#include "MdiClient.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

namespace Shutters {

MdiClient::MdiClient()
{
	using namespace ShuttersImpl;

	CLIENTCREATESTRUCT clientcreate;
	clientcreate.hWindowMenu = 0;
	clientcreate.idFirstChild = 50000;

	HWND handle = ::CreateWindow(
			L"MDICLIENT",
			0,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
			0,
			0,
			0,
			0,
			getNurserWindow(),
			(HMENU)1,
			::GetModuleHandle(0),
			&clientcreate
		);

	_ASSERTE(handle);

	setOldWndProc(replaceWndProc(handle, S_WndProc));
	setHandle(handle);
	addToMap(handle);
}

MdiClient::~MdiClient()
{
}

}
