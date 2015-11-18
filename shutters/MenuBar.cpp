#include "wincpp.hpp"
#include "MenuBar.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

MenuBar::MenuBar()
{
	m_hMenu = ::CreateMenu();
}

MenuBar::~MenuBar()
{
	disposeSelf();
}

void
MenuBar::dispose()
{
	disposeSelf();
	Base::dispose();
}

void
MenuBar::disposeSelf()
{
}
