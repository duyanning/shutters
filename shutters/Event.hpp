#ifndef SHUTTERS_EVENT_HPP
#define SHUTTERS_EVENT_HPP

#include "EVENT_TYPE.hpp"
//#include "EventArgs.hpp"

namespace Shutters {

	class EventArgs;
	class Component;
	EVENT_TYPE(Event, (Component* sender, EventArgs& e), (sender, e));

}

#endif
