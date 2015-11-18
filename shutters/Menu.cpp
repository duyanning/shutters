#include "wincpp.hpp"
#include "Menu.hpp"
#include "SubMenu.hpp"
#include "CommandItem.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

Menu::Menu()
:
	m_hMenu(0)
{
}

Menu::~Menu()
{
	disposeSelf();
}

void
Menu::insert(SubMenu& subMenu)
{
	insert(&subMenu);
}

void
Menu::insert(SubMenu* subMenu)
{
	::AppendMenu(m_hMenu, MF_POPUP | MF_STRING, (UINT_PTR)subMenu->handle(), subMenu->m_text.c_str());
	m_items.insert(subMenu);
	subMenu->m_parentMenu = this;
}

void
Menu::insert(CommandItem& cmd)
{
	insert(&cmd);
}

void
Menu::insert(CommandItem* cmd)
{
	//MENUITEMINFO menuItemInfo;
	//menuItemInfo.cbSize = sizeof menuItemInfo;
	//menuItemInfo.fType = MFT_STRING;
	//menuItemInfo.dwTypeData = "abc";
	//menuItemInfo.cch = 3;
	//::InsertMenuItem(m_hMenu, 0, TRUE, &menuItemInfo);
	::AppendMenu(m_hMenu, MF_STRING, cmd->getId(), cmd->m_text.c_str());
	m_items.insert(cmd);
	cmd->m_parentMenu = this;
}

void
Menu::destroyHandle()
{
	if (m_hMenu) {
		// cut off relation between Menu handle and SubMenu handle
		for (Items::iterator i = m_items.begin(); i != m_items.end(); ++i) {
			SubMenu* subMenu = dynamic_cast<SubMenu*>(*i);
			if (subMenu) {
				::RemoveMenu(handle(), (UINT)subMenu->handle(), MF_BYCOMMAND);
			}
		}

		::DestroyMenu(m_hMenu);
		m_hMenu = 0;
	}
}

void
Menu::disposeSelf()
{
	// todo
	//std::set<MenuItem*>::iterator i;
	//for (i = m_items.begin(); i != m_items.end(); ++i) {
	//	(*i)->dispose();
	//}
	//m_items.clear();

	destroyHandle();
}

void
Menu::dispose()
{
	disposeSelf();
	// Base::dispose();  // Menu has no Base
}
