#include <shutters/Shutters.hpp>

#include <shutters/MsgBox.hpp>
#include <shutters/FrameWindow.hpp>
#include <shutters/Button.hpp>
#include <shutters/GdiplusManager.hpp>

#include <sstream>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace std;
using namespace Shutters;

class MainWindow : public FrameWindow {
public:
	MainWindow();

	void MainWindow_mouseDown(Window* sender, MouseEventArgs& e);
	void MainWindow_mouseUp(Window* sender, MouseEventArgs& e);
	void MainWindow_mouseMove(Window* sender, MouseEventArgs& e);
	void MainWindow_paint(Window* sender, PaintEventArgs& e);
	void MainWindow_closing(Window* sender, CancelEventArgs& e);
private:
	bool m_leftBtnDown;
};

MainWindow::MainWindow()
:
	m_leftBtnDown(false)
{
	mouseDown.addListener(this, &MainWindow::MainWindow_mouseDown);
	mouseUp.addListener(this, &MainWindow::MainWindow_mouseUp);
	mouseMove.addListener(this, &MainWindow::MainWindow_mouseMove);
	paint.addListener(this, &MainWindow::MainWindow_paint);
	closing.addListener(this, &MainWindow::MainWindow_closing);

}

void
MainWindow::MainWindow_closing(Window* sender, CancelEventArgs& e)
{
	if (MsgBox(this, L"Are you sure?", L"WARNING", MB_YESNO) ==  IDNO)
		e.cancel = true;
}

void
MainWindow::MainWindow_paint(Window* sender, PaintEventArgs& e)
{
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 255));
	e.graphics.DrawLine(&pen, 0, 0, 100, 100);
}

void
MainWindow::MainWindow_mouseDown(Window* sender, MouseEventArgs& e)
{
	m_leftBtnDown = true;
}

void
MainWindow::MainWindow_mouseUp(Window* sender, MouseEventArgs& e)
{
	m_leftBtnDown = false;
}

void
MainWindow::MainWindow_mouseMove(Window* sender, MouseEventArgs& e)
{
	if (!m_leftBtnDown)  return;

	HDC hdc = ::GetDC(handle());

	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 255));
	graphics.DrawEllipse(&pen, e.X - 10, e.Y - 10, 20, 20);

	::ReleaseDC(handle(), hdc);
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
