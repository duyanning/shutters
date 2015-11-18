#include <shutters/Shutters.hpp>

#include <shutters/MenuBar.hpp>
#include <shutters/SubMenu.hpp>
#include <shutters/CommandItem.hpp>
#include <shutters/MsgBox.hpp>
#include <shutters/FrameWindow.hpp>
#include <shutters/GdiplusManager.hpp>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

int nTopLevelWnd;

class MainWindow : public FrameWindow {
	typedef FrameWindow Base;
	MenuBar menuBar;
		SubMenu fileMenu;
			CommandItem newCmd;
public:

	void onClosed(EventArgs& e)
	{
		Base::onClosed(e);
		delete this;

		if (--nTopLevelWnd == 0)
			::PostQuitMessage(0);
	}

	void newCmd_click(void*, EventArgs&)
	{
		MainWindow* newWindow = new MainWindow;
		newWindow->show();
		newWindow->update();
	}

	MainWindow()
	{
		nTopLevelWnd++;


		fileMenu.setText(L"File");
		menuBar.insert(fileMenu);
		newCmd.setText(L"New Window");
		newCmd.click.addListener(this, &MainWindow::newCmd_click);
		fileMenu.insert(newCmd);

		setMenu(menuBar);
	}

};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GdiplusManager gdiplus;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MainWindow* mainWindow = new MainWindow;
	mainWindow->show();
	mainWindow->update();

	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}
