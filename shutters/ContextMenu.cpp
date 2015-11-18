#include "wincpp.hpp"
#include "ContextMenu.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

ContextMenu::ContextMenu()
{
	m_hMenu = ::CreatePopupMenu();
}

ContextMenu::~ContextMenu()
{
	disposeSelf();
}

void
ContextMenu::dispose()
{
	disposeSelf();
	Base::dispose();
}

void
ContextMenu::disposeSelf()
{
}
