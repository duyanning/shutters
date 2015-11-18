#pragma once

#include "ListBox.hpp"

namespace Shutters {
	using namespace std;

	template <class T>
	class TListBox : public ListBox {
		typedef ListBox Base;
	public:
		void add(const wstring& s, T value);
		T selectedValue();
		std::pair<std::wstring, T> selectedItem();
	protected:
	private:
		std::map<int, T> m_items;
	};

	template <class T>
	void
	TListBox<T>::add(const wstring& s, T value)
	{
		int index = Base::add(s);
		m_items[index] = value;
	}

	template <class T>
	T
	TListBox<T>::selectedValue()
	{
		int index = selectedIndex();
		return index == -1 ? T() : m_items[index];
	}

	template <class T>
	pair<wstring, T>
	TListBox<T>::selectedItem()
	{
		// todo
		return make_pair(L"", selectedValue());
	}

}
