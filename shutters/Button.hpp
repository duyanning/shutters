#ifndef SHUTTERS_BUTTON_HPP
#define SHUTTERS_BUTTON_HPP

//#include "ChildWindow.hpp"
#include "ButtonBase.hpp"

namespace Shutters {

	using namespace std;

class Button : public ButtonBase {
	typedef ButtonBase Base;
public:
	Button(const wstring& text = L"");
	~Button();
protected:
private:
};

}

#endif
