#ifndef SHUTTERS_CANCELEVENT_HPP
#define SHUTTERS_CANCELEVENT_HPP

#include "EVENT_TYPE.hpp"
#include "CancelEventArgs.hpp"

namespace Shutters {

	class Window;
	EVENT_TYPE(CancelEvent, (Window* sender, CancelEventArgs& e), (sender, e));

}

#endif
