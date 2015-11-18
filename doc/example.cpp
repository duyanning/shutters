#include <shutters/Shutters.hpp>
#include <shutters/FrameWindow.hpp>
#include <shutters/Button.hpp>
#include <shutters/Label.hpp>

using namespace Shutters;

class MainWindow : public FrameWindow {
	Button button1;
	Label label1;
public:
	MainWindow();
	void button1_click(void*, EventArgs&);
};

MainWindow::MainWindow()
{
	button1.setText("C++");
	controls.add(button1);
	button1.setBounds(200, 50, 75, 20);
	button1.click.addListener(this, &MainWindow::button1_click);

	label1.setText("Hello, Shutters!");
	controls.add(label1);
	label1.setBounds(10, 50, 100, 80);
}

void
MainWindow::button1_click(void*, EventArgs&)
{
	label1.setEnabled(!label1.isEnabled());
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MainWindow mainWindow;
	mainWindow.show();
	mainWindow.update();

	Shutters::SetStartupWindow(mainWindow);

	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return msg.wParam ;
}
