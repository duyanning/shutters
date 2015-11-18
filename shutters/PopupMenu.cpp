#include "wincpp.hpp"
#include "PopupMenu.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

PopupMenu::PopupMenu()
{
	m_hMenu = ::CreatePopupMenu();
}

PopupMenu::~PopupMenu()
{
	disposeSelf();
}

void
PopupMenu::addSeparator()
{
	::AppendMenu(m_hMenu, MF_SEPARATOR, 0, 0);
}

void
PopupMenu::dispose()
{
	disposeSelf();
	Base::dispose();
}

void
PopupMenu::disposeSelf()
{
}
