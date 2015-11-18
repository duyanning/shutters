#include "wincpp.hpp"
#include "Window.hpp"
#include "MouseEventArgs.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

namespace Shutters {

	void
	Window::onMouseDown(MouseEventArgs& e)
	{
		Msg& msg = S_LastMsg();
		*msg.processed = true;
		*msg.result = 0;
		mouseDown.fire(this, e);
	}

	void
	Window::onMouseUp(MouseEventArgs& e)
	{
		Msg& msg = S_LastMsg();
		*msg.processed = true;
		*msg.result = 0;
		mouseUp.fire(this, e);
	}

	void
	Window::onMouseMove(MouseEventArgs& e)
	{
		Msg& msg = S_LastMsg();
		*msg.processed = true;
		*msg.result = 0;
		mouseMove.fire(this, e);
	}

}
