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

	Panel panel;
	Button button1;
	Button button2;
	CheckBox checkBox;
	RadioButton radioButton1;
	RadioButton radioButton2;
	RadioButton radioButton3;
	RadioButton radioButton4;
	RadioButton radioButton5;
	TextBox textBox1;
	TextBox textBox2;
	ListBox listBox;
	Label label1;
	Label label2;
	Gdiplus::Image image;

public:
	MainWindow();
	void button1_click(void*, EventArgs&);
	void button2_click(void*, EventArgs&);
	void textBox1_textChanged(void*, EventArgs&);
};
