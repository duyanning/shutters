#pragma once

#include "WinControl.hpp"

namespace Shutters {

	class ListControl : public WinControl {
		typedef WinControl Base;
	public:
		ListControl();
		~ListControl();
//		void add(const wstring& text);

		//template <class Iter>
		//void setDataSource(Iter begin, Iter end);
		//std::pair<Iter, Iter> getDataSourece();

		//template <class T>
		//void setDisplayMember();
		//getDisplayMember();

		//wstring getSelectedItem();
		//void setSelectedItem(const wstring& item);

		//int getSelectedIndex();
		//void setSelectedIndex(int index);

		//getSelectedValue();
		//void setSelectedValue();

		//wsting getItemText(void* item);
	protected:
	private:
	};

}
