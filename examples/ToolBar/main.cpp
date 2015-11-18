#include <shutters/Shutters.hpp>

#include <shutters/FrameWindow.hpp>
#include <shutters/ToolBar.hpp>
#include <shutters/StatusBar.hpp>
#include <shutters/GdiplusManager.hpp>
#include <shutters/Point.hpp>
#include <shutters/Size.hpp>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace std;
using namespace Shutters;

class MainWindow : public FrameWindow {
public:
	MainWindow();
private:
	ToolBar toolBar;
	StatusBar statusBar;
};

MainWindow::MainWindow()
{
	toolBar.setLocation(Point(10, 100));
	toolBar.setSize(Size(500, 20));
	toolBar.add(L"hello");
	controls.add(toolBar);

	statusBar.setLocation(Point(10, 100));
	statusBar.setSize(Size(500, 20));
	controls.add(statusBar);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GdiplusManager gdiplus;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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
