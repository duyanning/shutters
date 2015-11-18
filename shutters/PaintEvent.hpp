#ifndef SHUTTERS_PAINTEVENT_HPP
#define SHUTTERS_PAINTEVENT_HPP

#include "EVENT_TYPE.hpp"
#include "PaintEventArgs.hpp"

namespace Shutters {

	class Window;
	EVENT_TYPE(PaintEvent, (Window* sender, PaintEventArgs& e), (sender, e));

}

#endif
