#include "MainWindow.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

void
MainWindow::button1_click(void*, EventArgs&)
{
	panel.setAutoScroll(true);
	newButton1.setBounds(
			0 + panel.autoScrollPosition().x,
			0 + panel.autoScrollPosition().y,
			75,
			20
		);
	newButton1.setText(L"button A");

	panel.controls.add(newButton1);
}

void
MainWindow::button2_click(void*, EventArgs&)
{
	panel.setAutoScroll(true);
	newButton2.setBounds(
			120 + panel.autoScrollPosition().x,
			0 + panel.autoScrollPosition().y,
			75,
			20
		);

	newButton2.setText(L"button B");
	panel.controls.add(newButton2);
}

MainWindow::MainWindow()
{
	button1.setText(L"button1");
	button1.setBounds(200, 10, 75, 20);
	this->controls.add(button1);
	button1.click.addListener(this, &MainWindow::button1_click);

	button2.setText(L"button2");
	button2.setBounds(200, 90, 75, 20);
	this->controls.add(button2);
	button2.click.addListener(this, &MainWindow::button2_click);

	panel.setBounds(5, 100, 180, 100);
	panel.setAutoScroll(true);
	this->controls.add(panel);
}
