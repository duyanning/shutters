#include "wincpp.hpp"
#include "NotifyIcon.hpp"
#include "Icon.hpp"
#include "CommandItem.hpp"
#include "EventArgs.hpp"

using namespace Shutters;

int NotifyIcon::nextId = 0;

NotifyIcon::NotifyIcon()
	:
m_added(false),
m_icon(0),
m_visible(false),
m_contextMenu(0)
{
	m_id = ++nextId;
	m_window.m_reference = this;
	updateIcon(m_visible); 
}

NotifyIcon::~NotifyIcon()
{
	updateIcon(false); 
}

void
NotifyIcon::updateIcon(bool showIconInTray)
{
    NOTIFYICONDATA data; 
 
    data.cbSize = sizeof (NOTIFYICONDATA); 

    data.uCallbackMessage = WM_TRAYMOUSEMESSAGE;
    data.uFlags = NIF_MESSAGE;

    data.hWnd = m_window.handle();
    data.uID = m_id; 
    data.hIcon = 0;
    data.szTip[0] = 0;
    if (m_icon) {
        data.uFlags |= NIF_ICON; 
        data.hIcon = m_icon->handle();
    } 
    data.uFlags |= NIF_TIP; 
    wcscpy(data.szTip, m_text.c_str());

    if (showIconInTray && m_icon) {
        if (!m_added) {
            ::Shell_NotifyIcon(NIM_ADD, &data);
            m_added = true; 
        }
        else { 
            ::Shell_NotifyIcon(NIM_MODIFY, &data); 
        }
    } 
    else if (m_added) {
        ::Shell_NotifyIcon(NIM_DELETE, &data);
        m_added = false;
    } 


}

void
NotifyIcon::setIcon(Icon* icon)
{
	m_icon = icon;
	updateIcon(m_visible);
}

void
NotifyIcon::setContextMenu(ContextMenu* menu)
{
	m_contextMenu = menu;
}

void
NotifyIcon::setText(const wstring& text)
{
	m_text = text;
    if (m_added) {
        updateIcon(true);
    } 

}

void
NotifyIcon::setVisible(bool visible)
{
    if (m_visible != visible) {
        updateIcon(visible); 
        m_visible = visible;
    }
}

void
NotifyIcon::showContextMenu()
{
	 if (m_contextMenu == 0)
		 return;

	POINT pt;
	GetCursorPos(&pt);

	// http://support.microsoft.com/kb/135788
	::SetForegroundWindow(m_window.handle());
	
	::TrackPopupMenu(m_contextMenu->handle(),
		//TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
		TPM_VERTICAL | TPM_RIGHTALIGN,
		pt.x, pt.y,
		0,
		m_window.handle(),
		0);

	::PostMessage(m_window.handle(), WM_NULL, 0, 0);
}

void
NotifyIcon::wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result)
{
	switch (message) {
	case WM_TRAYMOUSEMESSAGE:
		switch (lParam) {
        case WM_LBUTTONDBLCLK:
		case WM_LBUTTONDOWN:
			EventArgs e;
			click.fire(this, e);

			break;
		case WM_RBUTTONUP:
			if (m_contextMenu) {
				showContextMenu(); 
			}

			break;
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
    case WM_DESTROY:
        updateIcon(false);
        break; 


	}
}


void
NotifyIcon::NotifyIconNativeWindow::wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result)
{
	m_reference->wndProc(message, wParam, lParam, processed, result);
}
