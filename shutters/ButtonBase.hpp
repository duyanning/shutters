#ifndef SHUTTERS_BUTTONBASE_HPP
#define SHUTTERS_BUTTONBASE_HPP

#include "WinControl.hpp"

namespace Shutters {

	using namespace std;

	class ButtonBase : public WinControl {
		typedef WinControl Base;
	public:
		ButtonBase(const wstring& text = L"");
		~ButtonBase();
	protected:
		void onClicked(EventArgs& e);
	};

}

#endif
