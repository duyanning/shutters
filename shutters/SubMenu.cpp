#include "wincpp.hpp"
#include "SubMenu.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

SubMenu::SubMenu(const wstring& text)
	: MenuItem(text)
{
}

SubMenu::~SubMenu()
{
	disposeSelf();
}

void
SubMenu::setText(const wstring& text)
{
	m_text = text;
	if (m_parentMenu) {
		::ModifyMenu(m_parentMenu->handle(), (UINT)handle(), MF_STRING | MF_BYCOMMAND | MF_POPUP, (UINT)handle(), m_text.c_str());
	}
}

void
SubMenu::dispose()
{
	disposeSelf();

	// Base::dispose();  // SubMenu has two Bases
	MenuItem::dispose();
	PopupMenu::dispose();
}

void
SubMenu::disposeSelf()
{
}
