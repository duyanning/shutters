#include "wincpp.hpp"

#include "Window.hpp"
#include "ChildWindow.hpp"
#include "MdiChildWindow.hpp"
#include "EventArgs.hpp"
#include "MouseEventArgs.hpp"
#include "PaintEventArgs.hpp"
#include "nurserWindow.hpp"

#include "Rectangle.hpp"
#include "Point.hpp"
#include "Size.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

namespace Shutters {

map<HWND, Window*> Window::handle_to_pointer_map;
bool Window::s_classRegistered = false;
Window::Msg Window::m_lastMsg;

Window::Window()
:
	controls(0),
	m_backColor(Window::defaultBackColor())
{
	controls.setOwner(this);
//	setBackColor(Window::defaultBackColor());
}

Window::~Window()
{
	disposeSelf();
}

HWND
Window::handle()
{
	return m_hWnd;
}

void
Window::setHandle(HWND handle)
{
	m_hWnd = handle;
	//addToMap(handle);
}

BOOL CALLBACK cut_off_relation_between_parent_and_children(HWND hChild, LPARAM lParam)
{
	HWND hParent = reinterpret_cast<HWND>(lParam);
	// skip descendants
	if (::GetParent(hChild) == hParent) {
		Window* child = Window::S_HandleToPointer(hChild);
		if (child) {
			::SetParent(hChild, ShuttersImpl::getNurserWindow());
		}

	}

	return TRUE;
}

/*
HWND
Window::createHandle()
{
	HWND h = ::CreateWindowEx();
	setHandle(h);
}
*/

HWND
Window::destroyHandle()
{
	using namespace ShuttersImpl;

	HWND oldHandle = handle();

	if (handle()) {
		// cut off relation between parent handle and children handle
		// todo: change below to use m_controls, be careful because children object may over before parent object, need to notify parent to change m_controls

		// reference the remarks part of GetWindow's document for not using GetWindow in a loop
		//for (HWND hChild = ::GetWindow(m_hWnd, GW_CHILD); hChild != NULL; hChild = ::GetWindow(hChild, GW_HWNDNEXT)) {
		//	Window* child = S_HandleToPointer(hChild);
		//	if (child) {
		//		::SetParent(child->handle(), ShuttersImpl::getNurserWindow());
		//	}
		//}

		::EnumChildWindows(m_hWnd, cut_off_relation_between_parent_and_children, reinterpret_cast<LPARAM>(m_hWnd));




		// be careful!
		// let m_hWnd = 0 before calling ::DestroyWindow(),
		// because while ::DestroyWindow(),
		// the handler of WM_NCDESTROY may delete this,
		// deleting this then will call destroyHandle() again!
		// let m_hWnd = 0 before calling ::DestroyWindow() can avoid reentrance.
		setHandle(0);
		::DestroyWindow(oldHandle);
	}

	return oldHandle;
}

void
Window::disposeSelf()
{
	// todo
	//for (HWND hChild = ::GetWindow(m_hWnd, GW_CHILD); hChild != NULL; hChild = ::GetWindow(hChild, GW_HWNDNEXT)) {
	//	Window* child = S_HandleToPointer(hChild);
	//	if (child)
	//		child->dispose();
	//}

	if (handle()) {
		removeFromMap(destroyHandle());
	}
}

void
Window::dispose()
{
	disposeSelf();
}

void
Window::addToMap(HWND hWnd)
{
	handle_to_pointer_map[hWnd] = this;
}

void
Window::removeFromMap(HWND hWnd)
{
	//if (!hWnd)
	//	hWnd = handle();
	handle_to_pointer_map.erase(hWnd);
}

void
Window::wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result)
{

	switch (message) {
	case WM_COMMAND:
	{
		HWND hwndCtl = (HWND)lParam;
		if (hwndCtl) {

			// because we cache current in S_WndProc, so we cannot call wndProc directly.
			//Window* This = S_HandleToPointer(hwndCtl);
			//This->wndProc(MSG_REFLECT_BASE + message, wParam, lParam, processed, result);
			::SendMessage(hwndCtl, MSG_REFLECT_BASE + message, wParam, lParam);

			// we forward notification to it's source to process.
			// whether they process or not,
			// we think we have processed it.
			processed = true;
			result = 0;
		}
		else {
			processed = false;
		}

	}
		break;
	//case WM_CTLCOLORBTN:
	//case WM_CTLCOLOREDIT:
	//case WM_CTLCOLORDLG:
	//case WM_CTLCOLORLISTBOX:
	//case WM_CTLCOLORSCROLLBAR:
	//case WM_CTLCOLORSTATIC:
	//{
	//	HWND hwndCtl = reinterpret_cast<HWND>(lParam);
	//	if (hwndCtl) {
	//		Window* This = S_HandleToPointer(hwndCtl);
	//		This->wndProc(MSG_REFLECT_BASE + message, wParam, lParam, processed, result);
	//		processed = true;
	//	}
	//}
	//break;
	//case WM_NCDESTROY:
	//	removeFromMap(handle());
	//	m_hWnd = 0;
	//	processed = true;
	//	break;
	case WM_ERASEBKGND:
	{
		HDC hdc = reinterpret_cast<HDC>(wParam);

		RECT rect;
		::GetClientRect(handle(), &rect);
		Gdiplus::Rect clientRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);

		Gdiplus::Graphics graphics(hdc);
		Gdiplus::SolidBrush brush(m_backColor);
		graphics.FillRectangle(&brush, clientRect);
		processed = true;
		result = !0;	// because we erase the background, so return nonzero.

	}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(handle(), &ps);
		//HDC hdc = ::GetDC(handle());
		//HDC hdc = 0;

		PaintEventArgs e(hdc);

//		Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 255));
//		e.graphics.DrawLine(&pen, 0, 0, 100, 100);

		onPaint(e);

		::EndPaint(handle(), &ps);
		//::ReleaseDC(handle(), hdc);

	}
		break;
	case WM_LBUTTONDOWN:
	{
		MouseEventArgs e;
		e.X = GET_X_LPARAM(lParam);
		e.Y = GET_Y_LPARAM(lParam);
		//::SetCapture(this->handle());  // will interfere the behavior of button
		onMouseDown(e);
		//processed = true;
	}
		break;
	case WM_LBUTTONUP:
	{
		MouseEventArgs e;
		e.X = GET_X_LPARAM(lParam);
		e.Y = GET_Y_LPARAM(lParam);
		//::ReleaseCapture();
		onMouseUp(e);
		//processed = true;
	}
		break;
	case WM_MOUSEMOVE:
	{
		MouseEventArgs e;
		e.X = GET_X_LPARAM(lParam);
		e.Y = GET_Y_LPARAM(lParam);
		onMouseMove(e);
		//processed = true;
	}
		break;
	default:
		processed = false;
		//onOthers();
		break;
	}
}

void
Window::saveLastMsg(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result)
{
	m_lastMsg.message = message;
	m_lastMsg.wParam = wParam;
	m_lastMsg.lParam = lParam;
	m_lastMsg.processed = &processed;
	m_lastMsg.result = &result;
}

LRESULT
Window::S_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (message == WM_COMMAND) {
		int x = 0;
		x++;
	}

	Window* This = S_HandleToPointer(hWnd);

	if (This) {

		LRESULT result = 0;	// only intialized for intialization, the value 0 has no assumed use
		bool processed = false;

		// save message infomations
		saveLastMsg(message, wParam, lParam, processed, result);
		//m_lastMsg.message = message;
		//m_lastMsg.wParam = wParam;
		//m_lastMsg.lParam = lParam;
		//m_lastMsg.processed = &processed;
		//m_lastMsg.result = &result;

		This->wndProc(message, wParam, lParam, processed, result);

		// only if processed == true, the content of result is valid.
		if (processed)
			return result;
	}

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT
Window::S_WndProcMdiFrame(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	Window* This = S_HandleToPointer(hWnd);

	if (This) {

		LRESULT result = 0;
		bool processed = false;
		saveLastMsg(message, wParam, lParam, processed, result);
		This->wndProc(message, wParam, lParam, processed, result);
		if (processed)
			return result;
	}
	

	HWND hwndClient = ::GetWindow(hWnd, GW_CHILD);
	return ::DefFrameProc(hWnd, hwndClient, message, wParam, lParam);
}

LRESULT
Window::S_WndProcMdiChild(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	Window* This = S_HandleToPointer(hWnd);

	if (This) {

		LRESULT result = 0;
		bool processed = false;
		saveLastMsg(message, wParam, lParam, processed, result);
		This->wndProc(message, wParam, lParam, processed, result);
		if (processed)
			return result;
	}
	

	return ::DefMDIChildProc(hWnd, message, wParam, lParam);
}

HWND
Window::S_CreateWindow(
		DWORD dwExStyle,      // extended window style
		LPCTSTR lpClassName,  // pointer to registered class name
		LPCTSTR lpWindowName, // pointer to window name
		DWORD dwStyle,        // window style
		int x,                // horizontal position of window
		int y,                // vertical position of window
		int nWidth,           // window width
		int nHeight,          // window height
		HWND hWndParent,      // handle to parent or owner window
		HMENU hMenu,          // handle to menu, or child-window identifier
		HINSTANCE hInstance,  // handle to application instance
		LPVOID lpParam        // pointer to window-creation data
	)
{
	S_RegisterClass(hInstance);
	
	return ::CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y,
			nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam
		);
}

void
Window::S_RegisterClass(HINSTANCE hInstance)
{
	if (s_classRegistered)  return;

	WNDCLASS wc;

//	wc.cbSize			= sizeof (WNDCLASSEX); 

	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= Window::S_WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= ::LoadIcon (NULL, IDI_APPLICATION);
	wc.hCursor			= ::LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wc.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
	wc.lpszMenuName		= 0;
	wc.lpszClassName	= L"ShuttersClass";
	//wcex.hIconSm		= 0;

	::RegisterClass(&wc);

	wc.lpfnWndProc = Window::S_WndProcMdiFrame;
	wc.lpszClassName	= L"ShuttersClassMdiFrame";
	::RegisterClass(&wc);

	wc.lpfnWndProc = Window::S_WndProcMdiChild;
	wc.lpszClassName	= L"ShuttersClassMdiChild";
	::RegisterClass(&wc);

	s_classRegistered = true;
}

void
Window::setVisible(bool b)
{
	if (b)
		::ShowWindow(m_hWnd, SW_SHOW);
	else
		::ShowWindow(m_hWnd, SW_HIDE);
}

bool
Window::visible()
{
	LONG style = GetWindowLong(m_hWnd, GWL_STYLE);
	return (style & WS_VISIBLE) != 0;
}

void
Window::setBounds(int x, int y, int width, int height)
{
	::MoveWindow(m_hWnd, x, y, width, height, TRUE);
}

void
Window::setBounds(const Rectangle& r)
{
	setBounds(r.x(), r.y(), r.width(), r.height());
}

Rectangle
Window::bounds()
{
	RECT bounds;
	::GetWindowRect(m_hWnd, &bounds);

	LONG style = ::GetWindowLong(m_hWnd, GWL_STYLE);

	if (style & WS_CHILD) {

		POINT pt;
		pt.x = bounds.left;
		pt.y = bounds.top;

		HWND parent = ::GetParent(m_hWnd);
		::ScreenToClient(parent, &pt);

		bounds.left = pt.x;
		bounds.top = pt.y;

		pt.x = bounds.right;
		pt.y = bounds.bottom;
		::ScreenToClient(parent, &pt);

		bounds.right = pt.x;
		bounds.bottom = pt.y;
	}

	return Rectangle(bounds.left, bounds.top, bounds.right - bounds.left, bounds.bottom - bounds.top);
}

int
Window::width()
{
	return bounds().width();
}

int
Window::height()
{
	return bounds().height();
}

void
Window::setSize(int width, int height)
{
	Rectangle bounds = this->bounds();
	setBounds(bounds.x(), bounds.y(), width, height);
}

void
Window::setSize(const Size& sz)
{
	setSize(sz.width, sz.height);
}

Size
Window::size()
{
	Rectangle bounds = this->bounds();
	return Size(bounds.width(), bounds.height());
}

//void
//Window::setClientSize(int width, int height)
//{
//}
//
//void
//Window::setClientSize(const Size& sz)
//{
//}
//
//Size
//Window::clientSize()
//{
//}

Window*
Window::S_HandleToPointer(HWND handle)
{
	map<HWND, Window*>::iterator pos = handle_to_pointer_map.find(handle);
	if (pos != handle_to_pointer_map.end())
		return pos->second;
	return 0;
}

void
Window::onClicked(EventArgs&)
{
}

void
Window::onTextChanged(EventArgs& e)
{
	textChanged.fire(this, e);
}

void
Window::onPaint(PaintEventArgs& e)
{
	Msg& msg = S_LastMsg();

	*msg.processed = true;
	*msg.result = 0;
	paint.fire(this, e);
}

void
Window::onControlAdded(ControlEventArgs&)
{
}

void
Window::onControlRemoved(ControlEventArgs&)
{
}

void
Window::setLocation(const Point& p)
{
	Rectangle rect = bounds();
	rect.setLocation(p);
	setBounds(rect);
}

void
Window::setLocation(int x, int y)
{
	setLocation(Point(x, y));
}

Point
Window::location()
{
	return bounds().location();
}

Point
Window::pointToScreen(const Point& client)
{
	POINT pt;
	pt.x = client.x;
	pt.y = client.y;
	::ClientToScreen(handle(), &pt);
	Point screen;
	screen.x = pt.x;
	screen.y = pt.y;
	return screen;
}

Point
Window::pointToClient(const Point& screen)
{
	POINT pt;
	pt.x = screen.x;
	pt.y = screen.y;
	::ClientToScreen(handle(), &pt);
	Point client;
	client.x = pt.x;
	client.y = pt.y;
	return client;
}

void
Window::setText(const wstring& text)
{
	EventArgs e;
	onTextChanged(e);
	::SetWindowTextW(m_hWnd, text.c_str());
}

void
Window::setForeColor(const Gdiplus::Color& color)
{
	//if (color == m_color)  return;
	m_foreColor = color;
	invalidate();
	//update();
}

const Gdiplus::Color&
Window::foreColor()
{
	return m_foreColor;
}

void
Window::setBackColor(const Gdiplus::Color& color)
{
	//if (color == m_color)  return;
	m_backColor = color;
	invalidate();
//	update();
}

const Gdiplus::Color&
Window::backColor()
{
	return m_backColor;
}

Gdiplus::Color
Window::defaultBackColor()
{
	COLORREF color = ::GetSysColor(COLOR_BTNFACE);
	return Gdiplus::Color(GetRValue(color), GetGValue(color), GetBValue(color));
}

wstring
Window::text()
{
	int length = ::GetWindowTextLengthW(handle());
	std::vector<wchar_t> buf(length + 1);
	::GetWindowTextW(handle(), &buf[0], static_cast<int>(buf.size()));
	return &buf[0];
}

void
Window::invalidate()
{
	::InvalidateRect(handle(), 0, TRUE);
}

void
Window::invalidate(const Rectangle& rc)
{
	RECT rect;
	rect.left = rc.left();
	rect.top = rc.top();
	rect.right = rc.right();
	rect.bottom = rc.bottom();

	::InvalidateRect(handle(), &rect, TRUE);
}

void
Window::update()
{
	::UpdateWindow(handle());
}

void
Window::setEnabled(bool b)
{
	::EnableWindow(m_hWnd, b ? TRUE : FALSE);
}

bool
Window::enabled()
{
	return ::IsWindowEnabled(m_hWnd) != 0;
}

void
Window::show()
{
	setVisible(true);
}

void
Window::hide()
{
	setVisible(false);
}

Window::Msg&
Window::S_LastMsg()
{
	return m_lastMsg;
}

bool
Window::capture()
{
	return ::GetCapture() == handle();
}

void
Window::setCapture(bool b)
{
	if (b) {
		if (!capture()) {
			::SetCapture(handle());
		}
	}
	else {
		if (capture()) {
			::ReleaseCapture();
		}
	}
}

Window*
Window::parent()
{
	return S_HandleToPointer(::GetParent(handle()));
}

void
Window::setParent(Window* p)
{
}

}
