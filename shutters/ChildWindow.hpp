#ifndef SHUTTERS_CHILDWINDOW_HPP
#define SHUTTERS_CHILDWINDOW_HPP

#include "Window.hpp"

namespace Shutters {

class ChildWindow : public Window {
	typedef Window Base;
public:
	ChildWindow();
	~ChildWindow();
	Window* getParent();
};

}

#endif
