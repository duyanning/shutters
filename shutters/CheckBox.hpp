#ifndef SHUTTERS_CHECKBOX_HPP
#define SHUTTERS_CHECKBOX_HPP

//#include "ChildWindow.hpp"
#include "ButtonBase.hpp"
#include "IStateOption.hpp"
#include "Event.hpp"

namespace Shutters {

	using namespace std;

//class CheckBox : public ButtonBase , public IStateOption {
class CheckBox : public ButtonBase {
	typedef ButtonBase Base;
public:
	CheckBox(const wstring& text = L"");
	~CheckBox();
	bool checked();
	void setChecked(bool b);

	// event
	Event checkedChanged;
protected:
	void onClicked(EventArgs& e);
private:
};

}

#endif