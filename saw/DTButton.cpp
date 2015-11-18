#include "DTButton.h"
#include <shutters/Rectangle.hpp>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

DTButton::DTButton()
{
	type = L"Button";
	name = L"button";
}

DTButton*
DTButton::clone()
{
	DTButton* button = new DTButton;
	button->setBounds(this->bounds());
	button->setText(L"button");
	return button;
}
