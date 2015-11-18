#pragma once

#include "WinControl.hpp"

namespace Shutters {

	using namespace std;

	class TextBoxBase : public WinControl {
		typedef WinControl Base;
	public:
		TextBoxBase();
		~TextBoxBase();
		virtual bool multiline();
		virtual void setMultiline(bool b);
	protected:
	private:
	};

}
