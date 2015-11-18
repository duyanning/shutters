#include "MainWindow.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

void
MainWindow::button1_click(void*, EventArgs&)
{
}

void
MainWindow::button2_click(void*, EventArgs&)
{
}


MainWindow::MainWindow()
{
	button1.setText(L"button 1");
	controls.add(button1);
	button1.setBounds(20, 50, 75, 20);
	button1.click.addListener(this, &MainWindow::button1_click);

	button2.setText(L"button 2");
	controls.add(button2);
	button2.setBounds(200, 50, 75, 20);
	button2.click.addListener(this, &MainWindow::button2_click);

}
