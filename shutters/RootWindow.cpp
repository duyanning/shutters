#include "wincpp.hpp"
#include "RootWindow.hpp"
#include "MenuBar.hpp"
#include "CommandItem.hpp"
#include "EventArgs.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

//RootWindow::RootWindow(RootWindow* owner)
RootWindow::RootWindow()
:
	m_menuBar(0),
	m_owner(0),
	m_isModal(false)
{
}

RootWindow::~RootWindow()
{
	disposeSelf();
}

void
RootWindow::disposeSelf()
{
	// todo
	//if (m_menuBar) {
	//	m_menuBar->dispose();
	//	m_menuBar = 0;
	//}
	// cut off relation between window handle and whose menu handle
	::SetMenu(handle(), 0);

}

void
RootWindow::dispose()
{
	disposeSelf();
	Base::dispose();
}

void
RootWindow::wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result)
{
	switch (message) {
	case WM_CREATE:
	{
		EventArgs e;
		onLoad(e);
		processed = true;
		result = 0;
	}
		break;
	case WM_CLOSE:
	{
		if (m_isModal) {
			dialogResult = Cancel;
			setVisible(false);
		}

		CancelEventArgs e;
		e.cancel = false;
		onClosing(e);

		if (!e.cancel) {
			if (!m_isModal)
				close();
		}

		processed = true;
	}
		break;
	//case WM_DESTROY:
	//	::SetMenu(handle(), 0);
	//	processed = true;
	//	break;
	case WM_NCDESTROY:
	{
		EventArgs e;
		onClosed(e);
		processed = true;
	}
		break;
	case WM_COMMAND:
	{
		if (lParam == 0) {	// from a menu
			WORD wID = LOWORD(wParam);
			CommandItem* This = CommandItem::S_IdToPointer(wID);
			//CommandItem* This = cmdItemId_to_this_map[wID];
			if (This) {	// 0 if comes from mdi min/max/restroe button on menu bar
				EventArgs e;
				This->click.fire(This, e);
				processed = true;
			}
		}

	}
		break;
	default:
		break;
	}

	Base::wndProc(message, wParam, lParam, processed, result);
}

void
RootWindow::setMenu(MenuBar& menuBar)
{
	setMenu(&menuBar);
}

void
RootWindow::setMenu(MenuBar* menuBar)
{
	m_menuBar = menuBar;
	::SetMenu(handle(), menuBar->handle());
}

RootWindow*
RootWindow::getOwner()
{
	return m_owner;
}

DialogResult
RootWindow::showDialog(RootWindow* owner)
{
	if (owner)
		m_owner = owner;
	m_isModal = true;
	dialogResult = None;
	Base::setVisible(true);

	bool bEnableParent = false;
	
	if (getOwner() && getOwner()->handle() != ::GetDesktopWindow())
	{
		getOwner()->setEnabled(false);
		bEnableParent = true;
	}

	MSG msg;
	while (dialogResult == None && ::GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	if (bEnableParent)
		getOwner()->setEnabled(true);

	return dialogResult;
}

void
RootWindow::onClosing(CancelEventArgs& e)
{
	closing.fire(this, e);
}

void
RootWindow::onClosed(EventArgs& e)
{
	closed.fire(this, e);
}

void
RootWindow::onLoad(EventArgs& e)
{
	load.fire(this, e);
}

void
RootWindow::close()
{
	dispose();
}

void
RootWindow::activate()
{
	::SetForegroundWindow(handle());
}