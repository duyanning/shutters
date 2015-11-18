#ifndef SHUTTERS_MOUSEEVENT_HPP
#define SHUTTERS_MOUSEEVENT_HPP

#include "EVENT_TYPE.hpp"
#include "MouseEventArgs.hpp"

namespace Shutters {

	class Window;
	EVENT_TYPE(MouseEvent, (Window* sender, MouseEventArgs& e), (sender, e));

}

#endif
