#include "wincpp.hpp"
#include "RadioButtonMenuItem.hpp"
#include "Menu.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

RadioButtonMenuItem::RadioButtonMenuItem(const wstring& text)
:
	Base(text)
{
	click.addListener(this, &RadioButtonMenuItem::handleClicked);
}

RadioButtonMenuItem::~RadioButtonMenuItem()
{
}

void
RadioButtonMenuItem::setChecked(bool b)
{
	if (b)
		::CheckMenuRadioItem(m_parentMenu->handle(), getId(), getId(), getId(), MF_BYCOMMAND);
	else
		::CheckMenuRadioItem(m_parentMenu->handle(), getId(), getId(), UINT(-1), MF_BYCOMMAND);
}

bool
RadioButtonMenuItem::checked()
{
	UINT checkState = ::GetMenuState(m_parentMenu->handle(), getId(), MF_BYCOMMAND);

	return (checkState & MF_CHECKED) != 0;
}

void
RadioButtonMenuItem::handleClicked(void*, EventArgs&)
{
	for (Menu::iterator i = m_parentMenu->begin(); i != m_parentMenu->end(); ++i) {
		RadioButtonMenuItem* radioItem = dynamic_cast<RadioButtonMenuItem*>(*i);
		if (radioItem && radioItem->getGroupId() == getGroupId())
			radioItem->setChecked(radioItem ==  this);
	}
}