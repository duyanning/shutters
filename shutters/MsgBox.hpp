#ifndef SHUTTERS_MSGBOX_HPP
#define SHUTTERS_MSGBOX_HPP

#include "wincpp.hpp"

namespace Shutters {

	using namespace std;

	class RootWindow;

	int MsgBox(RootWindow* owner, const wstring& text, const wstring& caption, UINT type);
}

#endif