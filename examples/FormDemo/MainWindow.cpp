#include "MainWindow.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

MainWindow::MainWindow()
{
	button1.setText(L"button1");
	controls.add(button1);
	button1.setBounds(200, 10, 75, 20);
	button1.click.addListener(this, &MainWindow::button1_click);

	button2.setText(L"button2");
	controls.add(button2);
	button2.setBounds(200, 40, 75, 20);
	button2.click.addListener(this, &MainWindow::button2_click);

	button3.setText(L"button3");
	controls.add(button3);
	button3.setBounds(200, 70, 75, 20);
	button3.click.addListener(this, &MainWindow::button3_click);

//	setIsMdiContainer(true);

	timer.tick.addListener(this, &MainWindow::timer_tick);
	timer.setInterval(2000);
	timer.start();
}

void
MainWindow::button1_click(void*, EventArgs&)
{
//	setIsMdiContainer(!isMdiContainer());
	//setIsMdiContainer(true);
}

void
MainWindow::button2_click(void*, EventArgs&)
{
	form1.show();
}

void
MainWindow::button3_click(void*, EventArgs&)
{
	form1.setMdiParent(this);
}

void
MainWindow::timer_tick(void*, EventArgs&)
{
	timer.stop();
	setIsMdiContainer(true);
}
