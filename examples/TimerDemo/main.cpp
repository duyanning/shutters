#include <shutters/Shutters.hpp>

#include <shutters/FrameWindow.hpp>
#include <shutters/Button.hpp>
#include <shutters/Timer.hpp>
#include <shutters/GdiplusManager.hpp>
#include <shutters/Point.hpp>
#include <shutters/Size.hpp>

#include <sstream>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace std;
using namespace Shutters;

class MainWindow : public FrameWindow {
public:
	MainWindow();

	void MainWindow_paint(Window* sender, PaintEventArgs& e);
	void timer_tick(void* sender, EventArgs& e);
	void btnStartStop_click(Component* sender, EventArgs& e);
private:
	int count;
	Timer timer;

	Button btnStartStop;
};

MainWindow::MainWindow()
:
	count(0)
{
	btnStartStop.setLocation(Point(10, 100));
	btnStartStop.setSize(Size(100, 20));
	btnStartStop.setText(L"Start/Stop");
	controls.add(btnStartStop);

	btnStartStop.click.addListener(this, &MainWindow::btnStartStop_click);

	paint.addListener(this, &MainWindow::MainWindow_paint);

	timer.tick.addListener(this, &MainWindow::timer_tick);
	timer.setInterval(1000);
	timer.start();
}

void
MainWindow::MainWindow_paint(Window* sender, PaintEventArgs& e)
{
	using namespace Gdiplus;

	HDC hdc = ::GetDC(handle());

	Graphics graphics(hdc);

	Font font(L"Arial", 36);
	PointF origin(0.0f, 0.0f);
	SolidBrush brush(Color(255, 0, 170, 0));

	wstringstream ss;
	ss << count;
	wstring text = ss.str();

	graphics.DrawString(text.c_str(), text.length(), &font, origin, &brush);

	::ReleaseDC(handle(), hdc);
}

void
MainWindow::timer_tick(void* sender, EventArgs& e)
{
	count++;
	invalidate();
}

void
MainWindow::btnStartStop_click(Component* sender, EventArgs& e)
{
	timer.setEnabled(!timer.enabled());
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
