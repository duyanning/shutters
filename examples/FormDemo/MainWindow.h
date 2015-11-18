#pragma once

#include <shutters/Shutters.hpp>
#include <shutters/Button.hpp>
#include <shutters/Form.hpp>
#include <shutters/Timer.hpp>
#include <Gdiplus.h>

using namespace Shutters;

class MainWindow : public Form {
	Button button1;
	Button button2;
	Button button3;
	Form form1;
	Timer timer;
public:
	MainWindow();
	void button1_click(void*, EventArgs&);
	void button2_click(void*, EventArgs&);
	void button3_click(void*, EventArgs&);
	void timer_tick(void*, EventArgs&);
};
