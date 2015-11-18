#include "wincpp.hpp"
#include "CheckBoxMenuItem.hpp"
#include "Menu.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

CheckBoxMenuItem::CheckBoxMenuItem(const wstring& text)
:
Base(text)
{
	click.addListener(this, &CheckBoxMenuItem::handleClicked);
}

CheckBoxMenuItem::~CheckBoxMenuItem()
{
}

void
CheckBoxMenuItem::setChecked(bool b)
{
	UINT checkState = (b ? MF_CHECKED : MF_UNCHECKED);
	::CheckMenuItem(m_parentMenu->handle(), getId(), MF_BYCOMMAND | checkState);
}

bool
CheckBoxMenuItem::checked()
{
	UINT checkState = ::GetMenuState(m_parentMenu->handle(), getId(), MF_BYCOMMAND);

	return (checkState & MF_CHECKED) != 0;
}

void
CheckBoxMenuItem::handleClicked(void*, EventArgs&)
{
	setChecked(!checked());
}