#include "wincpp.hpp"

#include "ListBox.hpp"
#include "nurserWindow.hpp"
#include "winHelpers.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

ListBox::ListBox()
{
	using namespace ShuttersImpl;

	HWND handle = ::CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"LISTBOX",
			L"",
			WS_VISIBLE | WS_CHILD,
			0,
			0,
			0,
			0,
			getNurserWindow(),
			NULL,
			0,
			NULL
		);

	setOldWndProc(replaceWndProc(handle, S_WndProc));
	setHandle(handle);
	addToMap(handle);
}

ListBox::~ListBox()
{
}

int
ListBox::add(const wstring& s)
{
	int index = ListBox_AddString(handle(), s.c_str());
	return index;
}

int
ListBox::selectedIndex()
{
	int index = ListBox_GetCurSel(handle());
	return index == LB_ERR ? -1 : index;
}

//void
//ListBox::setSelectedIndex(int index)
//{
//	ListBox_SetCurSel(handle(), index);
//}
//
//std::wstring
//ListBox::selectedValue()
//{
//	int index = selectedIndex();
//	if (index == -1)  return L"";
//
//	int len = ListBox_GetTextLen(handle(), index);
//	std::vector<wchar_t> text(len + 1);
//	ListBox_GetText(handle(), index, &text[0]);
//	return &text[0];
//}
//
//void
//ListBox::setSelectedValue(const wstring& value)
//{
//}

//
//T
//ListBox<T>::getSelectedItem()
//{
//	int index = getSelectedIndex();
//	return index == -1 ? T() : m_items[index];
//}
