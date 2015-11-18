#pragma once

//#include "ChildWindow.hpp"
#include "ButtonBase.hpp"
#include "IMutuallyExclusiveOption.hpp"
#include "Event.hpp"

namespace Shutters {

	using namespace std;

class RadioButton : public ButtonBase, public IMutuallyExclusiveOption {
//class RadioButton : public ButtonBase {
	typedef ButtonBase Base;
public:
	RadioButton(const wstring& text = L"");
	~RadioButton();
	bool checked();
	void setChecked(bool b);

	// event
	Event checkedChanged;
protected:
	void onClicked(EventArgs& e);

private:
};

}
