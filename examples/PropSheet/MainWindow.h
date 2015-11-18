#pragma once

#include <shutters/Shutters.hpp>
#include <shutters/Button.hpp>
#include <shutters/CheckBox.hpp>
#include <shutters/RadioButton.hpp>
#include <shutters/TextBox.hpp>
#include <shutters/ListBox.hpp>
#include <shutters/Label.hpp>
#include <shutters/MsgBox.hpp>
#include <shutters/FrameWindow.hpp>
#include <shutters/Panel.hpp>
#include <Gdiplus.h>

using namespace Shutters;

class MainWindow : public FrameWindow {


	Button button1;
	Button button2;


public:
	MainWindow();
	void button1_click(void*, EventArgs&);
	void button2_click(void*, EventArgs&);
};
