#pragma once

#include "ListControl.hpp"

namespace Shutters {

	class ListBox : public ListControl {
		typedef ListControl Base;
	public:
		ListBox();
		~ListBox();

		// properties:
		//items;

		int selectedIndex();
		//void setSelectedIndex(int index);

		//std::wstring selectedValue();
		//void setSelectedValue(const wstring& value);

		//selectedIndices

		// mothods:
		int add(const wstring& s);
		//void clearSelected();
		//bool getSelected(int index);
		//int findString(const wstring& s, int startIndex = 0);
		//int findStringExact(const wstring& s, int startIndex = 0);
	protected:
	private:
	};

}
