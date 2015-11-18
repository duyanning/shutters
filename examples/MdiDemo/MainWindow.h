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

class MainWindow : public MdiFrameWindow {

public:
	static bool menuBuilt;
	static MenuBar mainMenuBar;
		static SubMenu fileMenu;
			static CommandItem newHelloCmd;
			static CommandItem newWorldCmd;
			static CommandItem closeCurrentCmd;

	void newHelloCmd_click(void*, EventArgs&);
	void newWorldCmd_click(void*, EventArgs&);
	void closeCurrentCmd_click(void*, EventArgs&);
	void buildMenu();
	MainWindow();
};
