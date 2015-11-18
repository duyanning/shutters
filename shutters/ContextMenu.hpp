#pragma once

#include "RootWindow.hpp"
#include "Menu.hpp"

namespace Shutters {

class ContextMenu : public Menu {
	typedef Menu Base;
	void add();
public:
	ContextMenu();
	~ContextMenu();
	void dispose();
private:
	void disposeSelf();
};

}