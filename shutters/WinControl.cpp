#include "wincpp.hpp"
#include "WinControl.hpp"
#include "EventArgs.hpp"


#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace Shutters;

WinControl::WinControl()
:
	m_oldWndProc(0)
{
}

WinControl::~WinControl()
{
}

void
WinControl::setOldWndProc(WNDPROC oldWndProc)
{
	m_oldWndProc = oldWndProc;
}

void
WinControl::wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result)
{
	if (message < MSG_REFLECT_BASE) {

		switch (message) {
		// overriding onMouseDown, onMouseUp, etc. in a derived class,
		// while not calling base class's onMouseDown, etc. will cause
		// native control not to act.
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MOUSEMOVE:
			Base::wndProc(message, wParam, lParam, processed, result);
			break;
		// oerrideing onPaint in a derived class,
		// but not calling base class's onPaint will NOT cause
		// native control not to act.
		case WM_PAINT:
		{
			// because Base::wndProc call ::BeginPaint/::EndPaint, it interfere with
			// native control, so we call onPaint directly.

			// fire paint event after native control has draw itself,
			// otherwise what event handler draw will be overwriten by native control.
			callOldWndProc();

			HDC hdc = ::GetDC(handle());
			PaintEventArgs e(hdc);
			onPaint(e);
			::ReleaseDC(handle(), hdc);

		}

		default:
			callOldWndProc();
			break;
		}


	}
	else {
		onReflected();
	}
}

void
WinControl::onMouseDown(MouseEventArgs& e)
{
	Base::onMouseDown(e);
	callOldWndProc();
}

void
WinControl::onMouseUp(MouseEventArgs& e)
{
	Base::onMouseUp(e);
	callOldWndProc();
}

void
WinControl::onMouseMove(MouseEventArgs& e)
{
	Base::onMouseMove(e);
	callOldWndProc();
}

void
WinControl::onReflected()
{
	// it is our own messages,
	// so we need not touch 'processed' and 'result'.

	Msg& msg = S_LastMsg();
	if (msg.message == MSG_REFLECT_BASE + WM_COMMAND) {

		WORD wNotifyCode = HIWORD(msg.wParam); // notification code 
//			WORD wID = LOWORD(msg.wParam);         // item, control, or accelerator identifier 
		HWND hwndCtl = reinterpret_cast<HWND>(msg.lParam);      // handle of control 
		if (wNotifyCode == BN_CLICKED) {
			EventArgs e;
			onClicked(e);
		}
		else if (wNotifyCode == EN_CHANGE) {
			EventArgs e;
			onTextChanged(e);
		}

	}
}

void
WinControl::callOldWndProc()
{
	Msg& msg = S_LastMsg();

	*msg.processed = true;
	*msg.result = ::CallWindowProc(m_oldWndProc, handle(), msg.message, msg.wParam, msg.lParam);
	//*msg.result = 0;
}
