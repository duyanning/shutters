#pragma once

#include <shutters/Shutters.hpp>

#include <shutters/Button.hpp>
#include <shutters/MenuBar.hpp>
#include <shutters/SubMenu.hpp>
#include <shutters/CommandItem.hpp>
#include <shutters/MsgBox.hpp>
#include <shutters/FrameWindow.hpp>
#include <shutters/MdiFrameWindow.hpp>
#include <shutters/MdiChildWindow.hpp>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

class HelloWindow : public MdiChildWindow {
	Button m_button;

	static bool menuBuilt;
	static MenuBar helloMenuBar;
		static SubMenu helloMenu;
			static CommandItem duCmd;
			static CommandItem yanCmd;
			static CommandItem ningCmd;

			Event::Connection cnDu;
			Event::Connection cnYan;
			Event::Connection cnNing;
public:
	void menu_click(void* sender, EventArgs& e);
	void onActivate(bool b);
	HelloWindow(MdiFrameWindow* mdiFrame);
	void buildMenu();
};
