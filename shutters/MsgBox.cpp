#include "wincpp.hpp"
#include "MsgBox.hpp"
#include "RootWindow.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

int Shutters::MsgBox(RootWindow* owner, const wstring& text, const wstring& caption, UINT type)
{
	return ::MessageBox(owner->handle(), text.c_str(), caption.c_str(), type);
}