#pragma once

#include <shutters/Shutters.hpp>
#include <shutters/Button.hpp>
#include <shutters/FrameWindow.hpp>
#include <shutters/Panel.hpp>

using namespace Shutters;

class MainWindow : public FrameWindow {
	Panel panel;
	Button button1;
	Button button2;
	Button newButton1;
	Button newButton2;
public:
	MainWindow();
	void button1_click(void*, EventArgs&);
	void button2_click(void*, EventArgs&);
};
