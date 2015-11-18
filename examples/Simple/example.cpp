#include <shutters/Shutters.hpp>
#include <shutters/FrameWindow.hpp>
#include <shutters/Button.hpp>
#include <shutters/Label.hpp>
#include <shutters/GdiplusManager.hpp>
#include <shutters/RadioButton.hpp>
#include <sstream>

using namespace Shutters;
using namespace std;

class MainWindow : public FrameWindow {
	Button button1;
	Label label1;
	//RadioButton radioButton1;
	//RadioButton radioButton2;
public:
	MainWindow();
	void button1_click(void*, EventArgs&);
};

MainWindow::MainWindow()
{
	button1.setText(L"C++");
	controls.add(button1);
	button1.setBounds(200, 50, 75, 20);
	button1.click.addListener(this, &MainWindow::button1_click);

	label1.setText(L"Hello, Shutters!");
	controls.add(label1);
	label1.setBounds(10, 50, 100, 80);

	//radioButton1.setText(L"radio1");
	//controls.add(radioButton1);
	//radioButton1.setBounds(200, 90, 75, 20);

	//radioButton2.setText(L"radio2");
	//controls.add(radioButton2);
	//radioButton2.setBounds(200, 120, 75, 20);
}

void
MainWindow::button1_click(void*, EventArgs&)
{
	//label1.setEnabled(!label1.enabled());
	wchar_t filename[MAX_PATH + 1];
	filename[0] = 0;
	
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof ofn);
	ofn.lStructSize = sizeof ofn;
	ofn.hwndOwner = handle();
    ofn.lpstrFilter = L"All Files (*.*)\0*.*\0Directories\0*|*\0\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = sizeof (filename);
    ofn.lpstrInitialDir = L"f:\\";
    ofn.lpstrTitle = L"hi";
    ofn.nFilterIndex = 1;

    ofn.Flags = (OFN_HIDEREADONLY | OFN_NOCHANGEDIR
			  | OFN_EXPLORER | OFN_ENABLEHOOK);

	//ofn.Flags |= OFN_FILEMUSTEXIST;

	BOOL ok = GetOpenFileName(&ofn);
	//BOOL ok = GetSaveFileName(&ofn);
	if (ok) {
		::MessageBox(handle(), filename, L"", MB_OK);
	}
	else {
		wstringstream ss;
		ss << hex << CommDlgExtendedError();
		wstring text = L"failed ";
		text +=	ss.str();

		::MessageBox(handle(), text.c_str(), L"", MB_OK);

	}


}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GdiplusManager gdiplus;

	MainWindow mainWindow;
	mainWindow.show();
	mainWindow.update();

	Shutters::SetStartupWindow(mainWindow);

	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}
