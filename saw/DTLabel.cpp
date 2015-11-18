#include "DTLabel.h"
#include <shutters/Rectangle.hpp>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

DTLabel::DTLabel()
{
	type = L"Label";
	name = L"label";
}

DTLabel*
DTLabel::clone()
{
	DTLabel* label = new DTLabel;
	label->setBounds(this->bounds());
	label->setText(L"label");
	return label;
}
