#pragma once

#include "RootWindow.hpp"
#include "Menu.hpp"

namespace Shutters {

class MenuBar : public Menu {
	typedef Menu Base;
	void add();
public:
	MenuBar();
	~MenuBar();
	void dispose();
private:
	void disposeSelf();
};

}