#pragma once

#include "MenuItem.hpp"
#include "PopupMenu.hpp"

namespace Shutters {

	class SubMenu : public MenuItem, public PopupMenu {
	public:
		SubMenu(const wstring& text = wstring());
		~SubMenu();
		void setText(const wstring& text);
		void dispose();
	private:
		void disposeSelf();
	};
};
