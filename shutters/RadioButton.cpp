#include "wincpp.hpp"
#include "RadioButton.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

RadioButton::RadioButton(const wstring& text)
{
	ShuttersImpl::modifyStyle(handle(), 0, BS_RADIOBUTTON);
}

RadioButton::~RadioButton()
{
}

void
RadioButton::onClicked(EventArgs& e)
{
	Base::onClicked(e);
	setChecked(true);
}

bool
RadioButton::checked()
{
	return ::SendMessage(handle(), BM_GETCHECK, 0, 0) == BST_CHECKED;
}

void
RadioButton::setChecked(bool b)
{
	if (b == checked())  return;

	HWND hParent = getParent()->handle();
	for (HWND hChild = ::GetWindow(hParent, GW_CHILD); hChild != NULL; hChild = ::GetWindow(hChild, GW_HWNDNEXT)) {
		Window* child = S_HandleToPointer(hChild);
		RadioButton* radioButton = dynamic_cast<RadioButton*>(child);
		if (radioButton && radioButton->getGroupId() == getGroupId()) {
			bool isMe;
			isMe = (radioButton == this);
			::SendMessage(radioButton->handle(), BM_SETCHECK, (isMe ? BST_CHECKED : BST_UNCHECKED), 0);
		}
	}

}
