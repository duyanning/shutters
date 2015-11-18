#include "wincpp.hpp"
#include "CheckBox.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"
#include "winHelpers.hpp"
#include "EventArgs.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

CheckBox::CheckBox(const wstring& text)
{
	ShuttersImpl::modifyStyle(handle(), 0, BS_CHECKBOX);
}

CheckBox::~CheckBox()
{
}

void
CheckBox::onClicked(EventArgs& e)
{
	Base::onClicked(e);
	setChecked(!checked());
}

bool
CheckBox::checked()
{
	return ::SendMessage(handle(), BM_GETCHECK, 0, 0) == BST_CHECKED;
}

void
CheckBox::setChecked(bool b)
{
	if (b == checked())  return;

	::SendMessage(handle(), BM_SETCHECK, (b ? BST_CHECKED : BST_UNCHECKED), 0);

	EventArgs cce;
	checkedChanged.fire(this, cce);
}
