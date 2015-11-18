#ifndef SHUTTERS_WINDOW_HPP
#define SHUTTERS_WINDOW_HPP

#include "Component.hpp"
#include "ControlCollection.hpp"
#include "Event.hpp"
#include "MouseEvent.hpp"
#include "PaintEvent.hpp"
#include "ControlEventArgs.hpp"

namespace Shutters {

	using namespace std;

	class ChildWindow;

	class Rectangle;
	class Point;
	class Size;

	class EventArgs;

	class Window : public Component {
	public:
		Window();
		virtual ~Window() = 0;
		virtual void dispose();

		void invalidate();
		void invalidate(const Rectangle& rc);
		void update();

		Window* parent();
		void setParent(Window*);
		virtual void setText(const wstring& text);
		virtual wstring text();

		virtual void setBackColor(const Gdiplus::Color& color);
		virtual const Gdiplus::Color& backColor();

		virtual void setForeColor(const Gdiplus::Color& color);
		virtual const Gdiplus::Color& foreColor();

		static Gdiplus::Color defaultBackColor();

		Rectangle bounds();
		void setBounds(const Rectangle& r);
		void setBounds(int x, int y, int width, int height);

		Point location();
		void setLocation(const Point& p);
		void setLocation(int x, int y);// no

		Size size();
		void setSize(const Size& s);
		void setSize(int width, int height);// no

		//Size clientSize();
		//void setclientSize(const Size& s);
		//void setclientSize(int width, int height);// no

		int width();
		void setWidth(int width);
		int height();
		void setHeight(int height);

		bool capture();
		void setCapture(bool b);

		void setVisible(bool b);
		bool visible();
		void show();
		void hide();

		void setEnabled(bool b);
		bool enabled();

		static HWND S_CreateWindow(
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
			);

		static bool s_classRegistered;
		static void S_RegisterClass(HINSTANCE hInstance);

		Point pointToScreen(const Point& p);
		Point pointToClient(const Point& p);
		HWND handle();

		// event
		Event click;
		Event textChanged;
		PaintEvent paint;
		MouseEvent mouseDown;
		MouseEvent mouseUp;
		MouseEvent mouseMove;

		// property
		ControlCollection controls;

		static Window* S_HandleToPointer(HWND);

	protected:
		void setHandle(HWND handle);
		
		virtual void wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result);
		static LRESULT CALLBACK S_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK S_WndProcMdiFrame(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK S_WndProcMdiChild(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		static const UINT MSG_REFLECT_BASE = 0xBC00;

		virtual void onClicked(EventArgs& e);
		virtual void onTextChanged(EventArgs& e);
		virtual void onPaint(PaintEventArgs& e);
		// mouse
		virtual void onMouseDown(MouseEventArgs& e);
		virtual void onMouseUp(MouseEventArgs& e);
		virtual void onMouseMove(MouseEventArgs& e);

		virtual void onControlAdded(ControlEventArgs& e);
		virtual void onControlRemoved(ControlEventArgs& e);

		struct Msg {
			UINT message;
			WPARAM wParam;
			LPARAM lParam;
			bool* processed;
			LRESULT* result;
		};
		static Msg& S_LastMsg();
		static void saveLastMsg(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result);

		//HWND createHandle();
		HWND destroyHandle();
		void addToMap(HWND hWnd);
		void removeFromMap(HWND hWnd);

	private:
		HWND m_hWnd;
		static Msg m_lastMsg;
		Gdiplus::Color m_backColor;
		Gdiplus::Color m_foreColor;
		//wstring m_text;

		static map<HWND, Window*> handle_to_pointer_map;
		void disposeSelf();	// non-virtual

		friend class ControlCollection;
	};

}

#endif
