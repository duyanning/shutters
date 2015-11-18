#pragma once

#include "TextBoxBase.hpp"

namespace Shutters {

	using namespace std;

	class TextBox : public TextBoxBase {
		typedef TextBoxBase Base;
	public:
		TextBox();
		~TextBox();
		bool multiline();
		void setMultiline(bool b);
	protected:
	private:
		HWND createNativeControl(bool multiline);
		bool m_multiline;
	};

}
