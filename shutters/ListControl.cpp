#include "wincpp.hpp"
#include "ListControl.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

ListControl::ListControl()
{
}

ListControl::~ListControl()
{
}

//void
//ListControl::add(const wstring& text)
//{
//	::SendMessage(handle(), LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(text.c_str()));
//}
//
//wstring
//ListControl::getSelectedItem()
//{
//	return L"";
//}
//
//int
//ListControl::getSelectedIndex()
//{
//	return 0;
//}
//
//void
//ListControl::setSelectedIndex(int index)
//{
//}
//
//wsting
//ListControl::getItemText(void* item)
//{
//	return L"";
//}
//
