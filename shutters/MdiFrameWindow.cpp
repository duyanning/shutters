#include "wincpp.hpp"
#include "MdiFrameWindow.hpp"
#include "MdiChildWindow.hpp"
#include "MenuBar.hpp"
#include "SubMenu.hpp"
#include "CommandItem.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

//MdiFrameWindow::MdiFrameWindow(RootWindow* owner)
MdiFrameWindow::MdiFrameWindow()
:
	//Base(owner),
	m_hwndClient(0)
{
	HWND handle = S_CreateWindow(
			0,
			L"ShuttersClassMdiFrame",
			L"",
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			//owner ? owner->handle() : 0,
			0,
			0,
			::GetModuleHandle(0),
			0
		);

	setHandle(handle);
	addToMap(handle);

	CLIENTCREATESTRUCT clientcreate;
	clientcreate.hWindowMenu = 0;
	clientcreate.idFirstChild = 50000;

	m_hwndClient = ::CreateWindow(
			L"MDICLIENT",
			0,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
			0,
			0,
			0,
			0,
			this->handle(),
			(HMENU)1,
			::GetModuleHandle(0),
			&clientcreate
		);

	_ASSERTE(m_hwndClient);
}

MdiFrameWindow::~MdiFrameWindow()
{
}

void
MdiFrameWindow::wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result)
{
	switch (message) {
	default:
		break;
	}

	Base::wndProc(message, wParam, lParam, processed, result);

	
	if (!processed && message == WM_COMMAND) {
		HWND hwndActiveChild = (HWND)::SendMessage(
				m_hwndClient,
				WM_MDIGETACTIVE,
				0,
				0
			);

		if (::IsWindow(hwndActiveChild))
			::SendMessage(hwndActiveChild, WM_COMMAND, wParam, lParam);
	}
	// add >>
	//processed = true;
	//result = ::DefFrameProc(handle(), m_hwndClient, message, wParam, lParam);
	// add <<
}

void
MdiFrameWindow::deleteChild(MdiChildWindow* child)
{
	destroyChild(child->handle());
}

HWND
MdiFrameWindow::createChild()
{
	MDICREATESTRUCT mdicreate;

	mdicreate.szClass = L"ShuttersClassMdiChild";
	mdicreate.szTitle = L"";
	mdicreate.hOwner = ::GetModuleHandle(0);
	mdicreate.x = CW_USEDEFAULT;
	mdicreate.y = CW_USEDEFAULT;
	mdicreate.cx = CW_USEDEFAULT;
	mdicreate.cy = CW_USEDEFAULT;
	mdicreate.style = 0;
	mdicreate.lParam = 0;
               
	HWND hwndChild = (HWND)::SendMessage(
			m_hwndClient,
			WM_MDICREATE,
			0,
			(LPARAM)(LPMDICREATESTRUCT)&mdicreate
		);

	_ASSERTE(hwndChild);

	return hwndChild;
}

void
MdiFrameWindow::destroyChild(HWND child)
{
	::SendMessage(m_hwndClient, WM_MDIDESTROY, (WPARAM)child, 0);
}

MdiChildWindow*
MdiFrameWindow::getActiveChild()
{
	HWND hwndChild = (HWND)::SendMessage(m_hwndClient, WM_MDIGETACTIVE, 0, 0);
	return static_cast<MdiChildWindow*>(S_HandleToPointer(hwndChild));
}

void
MdiFrameWindow::setMdiMenu(MenuBar& menuBar, SubMenu* windowMenu)
{
	setMdiMenu(&menuBar, windowMenu);
}

void
MdiFrameWindow::setMdiMenu(MenuBar* menuBar, SubMenu* windowMenu)
{
	setMdiMenu(menuBar->handle(), windowMenu ? windowMenu->handle() : 0);
}

void
MdiFrameWindow::setMdiMenu(HMENU hMenuBar, HMENU hWindowMenu)
{
	::SendMessage(m_hwndClient, WM_MDISETMENU, (WPARAM)hMenuBar, (LPARAM)hWindowMenu);
	::DrawMenuBar(handle());
}
