#include "wincpp.hpp"
#include "Form.hpp"
#include "MenuBar.hpp"
#include "CommandItem.hpp"
#include "EventArgs.hpp"
#include "MdiClient.hpp"
#include "winHelpers.hpp"
#include "Rectangle.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

Form::Form()
:
	m_menuBar(0),
	m_owner(0),
	m_isModal(false),
	m_isMdiContainer(false),
	m_isMdiChild(false),
	m_hwndClient(0),
	m_mdiClient(0),
	m_ourMenuBar(false)
{
	HWND handle = S_CreateWindow(
			0,
			L"ShuttersClass",
			L"",
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			::GetModuleHandle(0),
			0
		);

	setHandle(handle);
	addToMap(handle);
}

Form::~Form()
{
	disposeSelf();
}

void
Form::disposeSelf()
{
	if (handle()) {
		delete m_mdiClient;
		m_mdiClient = 0;

		if (m_ourMenuBar) {
			delete m_menuBar;
		}
		else {
			// cut off relation between window handle and whose menu handle
			::SetMenu(handle(), 0);
		}
	}
}

void
Form::dispose()
{
	disposeSelf();
	Base::dispose();
}

void
Form::wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result)
{
	if (message == WM_SYSCOMMAND) {
		int x = 0;
		x++;
	}

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
	//case WM_SIZE:
	//{
	//	int width = LOWORD(lParam);
	//	int height = HIWORD(lParam);
	//	if (m_mdiClient) {
	//		m_mdiClient->setSize(width, height);
	//	}
	//}
	//	break;
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
	case WM_MDIACTIVATE:
	{
		if (!menu()) {
			// we need a menu bar so that mdi client could draw min/max button on it
			m_ourMenuBar = true;
			setMenu(new MenuBar);
		}

		// set child's menu if gaining focus
		if (lParam == (LPARAM)handle()) {
			HWND hwndClient = ::GetParent(handle());
			::SendMessage(
					hwndClient, WM_MDISETMENU,
					(WPARAM)menu()->handle(), (LPARAM)0
				);
		}

		// set parent's menu if losing focus
		if (lParam != (LPARAM)handle()) {
			HWND hwndClient = ::GetParent(handle());
			::SendMessage(
					hwndClient, WM_MDISETMENU,
					(WPARAM)mdiParent()->menu()->handle(),
					(LPARAM)0
				);
		}

		EventArgs e;
		onMdiChildActivate(e);
	}
		break;
	default:
		break;
	}

	Base::wndProc(message, wParam, lParam, processed, result);

//	if (m_isMdiContainer && m_mdiClient) {
	//	processed = true;
	//	result = ::DefFrameProc(handle(), m_mdiClient->handle(), message, wParam, lParam);
	//}
//	if (m_isMdiContainer && m_hwndClient) {
	if (m_isMdiContainer) {
		processed = true;
		result = ::DefFrameProc(handle(), m_hwndClient, message, wParam, lParam);
	}
	else if (m_isMdiChild) {
		processed = true;
		result = ::DefMDIChildProc(handle(), message, wParam, lParam);
	}
}

void
Form::setMenu(MenuBar& menuBar)
{
	setMenu(&menuBar);
}

void
Form::setMenu(MenuBar* menuBar)
{
	m_menuBar = menuBar;
	::SetMenu(handle(), menuBar->handle());
}

MenuBar*
Form::menu()
{
	return m_menuBar;
}

Form*
Form::getOwner()
{
	return m_owner;
}

DialogResult
Form::showDialog(Form* owner)
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
Form::onClosing(CancelEventArgs& e)
{
	closing.fire(this, e);
}

void
Form::onClosed(EventArgs& e)
{
	closed.fire(this, e);
}

void
Form::onLoad(EventArgs& e)
{
	load.fire(this, e);
}

void
Form::close()
{
	dispose();
}

bool
Form::isMdiContainer()
{
	return m_isMdiContainer;
}

void
Form::setIsMdiContainer(bool is)
{
	if (is == m_isMdiContainer)  return;
	m_isMdiContainer = is;

	if (m_isMdiContainer) {

		// create mdi client

		//m_mdiClient = new MdiClient;
		//this->controls.add(m_mdiClient);
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

		// resize mdi client to occupy the client area of mdi parent.
		// we must do it manually becasue we do NOT create it while creating mdi parent.
		RECT bounds;
		::GetClientRect(handle(), &bounds);
		::MoveWindow(m_hwndClient, bounds.left, bounds.top,
				bounds.right - bounds.left,
				bounds.bottom - bounds.top, TRUE
			);
		//RECT clientRect;
		//::GetClientRect(handle(), &clientRect);
		//m_mdiClient->setSize(clientRect.right - clientRect.left,
		//						clientRect.bottom - clientRect.top);
	}
	else {
		// todo
		// destroy mdi client
	}
}

Form*
Form::mdiParent()
{
	if (!isMdiChild())  return 0;
	HWND hMdiParent = ::GetParent(::GetParent(handle()));
	return static_cast<Form*>(S_HandleToPointer(hMdiParent));
}

void
Form::setMdiParent(Form* p)
{
	if (!p->isMdiContainer())  return;
	if (p == mdiParent())  return;
	m_isMdiChild = true;

	/*
		When you call the SetParent function to allow a standard form to become
		a child form of a multiple-document interface (MDI) application,
		many child windowing features do not work.
		This problem occurs because, by design, a standard window cannot
		be completely altered at run time to mimic a child window.
		http://support.microsoft.com/kb/253814
	*/


	// create new one
	MDICREATESTRUCT mdicreate;

	mdicreate.szClass = L"ShuttersClass";
	mdicreate.szTitle = L"";
	mdicreate.hOwner = ::GetModuleHandle(0);
	mdicreate.x = CW_USEDEFAULT;
	mdicreate.y = CW_USEDEFAULT;
	mdicreate.cx = CW_USEDEFAULT;
	mdicreate.cy = CW_USEDEFAULT;
	mdicreate.style = 0;
	mdicreate.lParam = 0;
               
	HWND newHandle = (HWND)::SendMessage(
			p->m_hwndClient,
			WM_MDICREATE,
			0,
			(LPARAM)(LPMDICREATESTRUCT)&mdicreate
		);

	_ASSERTE(newHandle);

	// let oldHandle's children be newHandle's children
	// ... not implemented.

	// destroy old one
	removeFromMap(destroyHandle());

	// install new one
	setHandle(newHandle);
	addToMap(newHandle);
}

bool
Form::isMdiChild()
{
	return m_isMdiChild;
}

void
Form::onMdiChildActivate(EventArgs& e)
{
}

void
Form::setIcon(Icon* icon)
{
}

Icon*
Form::getIcon()
{
	return 0;
}

