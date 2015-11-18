#include "MainWindow.h"
#include "AboutDialog.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

void
MainWindow::button1_click(void*, EventArgs&)
{
	textBox1.setEnabled(!textBox1.enabled());
	button2.setText(button2.enabled() ? L"diabled" : L"enabled");
	button2.setEnabled(!button2.enabled());
}

void
MainWindow::button2_click(void*, EventArgs&)
{
	AboutDialog dlg;
	if (dlg.showDialog(this) == OK) {
		int x = 0;
		x++;
	}
}

void
MainWindow::textBox1_textChanged(void*, EventArgs&)
{
	label1.setText(textBox1.text());
}

MainWindow::MainWindow()
:
	//image(L"marx.jpg")
image(L"F:\\freechmzoomer\\res\\ico00001.ico")
{
	controls.add(label2);
	label2.setBounds(400, 100, 10, 10);
	label2.setSize(image.GetWidth(), image.GetHeight());
	label2.setImage(&image);

	panel.setBounds(5, 5, 180, 100);
	this->controls.add(panel);

	label1.setText(L"Label");
	label1.setBounds(100, 10, 75, 20);
//	controls.add(Label);
	panel.controls.add(label1);

	button1.setText(L"OK");
	controls.add(button1);
	button1.setBounds(200, 10, 75, 20);
	button1.click.addListener(this, &MainWindow::button1_click);

	checkBox.setText(L"option1");
	controls.add(checkBox);
	checkBox.setBounds(200, 60, 75, 20);

	radioButton1.setText(L"radio1");
	controls.add(radioButton1);
	radioButton1.setBounds(200, 90, 75, 20);

	radioButton2.setText(L"radio2");
	controls.add(radioButton2);
	radioButton2.setBounds(200, 120, 75, 20);

	radioButton3.setText(L"radio3");
	controls.add(radioButton3);
	radioButton3.setBounds(200, 150, 75, 20);

	radioButton4.setText(L"radio4");
	radioButton4.setGroupId(1);
	controls.add(radioButton4);
	radioButton4.setBounds(300, 90, 75, 20);

	radioButton5.setText(L"radio5");
	radioButton5.setGroupId(1);
	controls.add(radioButton5);
	radioButton5.setBounds(300, 120, 75, 20);

	button2.setText(L"enabled");
	controls.add(button2);
	button2.setBounds(400, 10, 75, 20);
	button2.click.addListener(this, &MainWindow::button2_click);

	controls.add(textBox1);
	textBox1.setBounds(10, 120, 100, 20);
	textBox1.textChanged.addListener(this, &MainWindow::textBox1_textChanged);

	controls.add(textBox2);
	textBox2.setBounds(10, 150, 100, 80);
	textBox2.setMultiline(true);

	controls.add(listBox);
	listBox.setBounds(200, 200, 100, 100);
	listBox.add(L"Windows");
	listBox.add(L"Shutters");
	listBox.add(L"C style API");
	listBox.add(L"C++ style API");
}
