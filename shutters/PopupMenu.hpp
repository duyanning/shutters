#pragma once

#include "Menu.hpp"

namespace Shutters {

	class PopupMenu : public Menu {
		typedef Menu Base;
	public:
		PopupMenu();
		virtual ~PopupMenu();
		void dispose();
		void addSeparator();
	private:
		void disposeSelf();
	};
};