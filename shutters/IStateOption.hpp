#pragma once

#include "EVENT_TYPE.hpp"

namespace Shutters {

	class IStateOption {
	public:
		EVENT_TYPE(EventChanged, (IStateOption* btn), (btn));
		EventChanged changed;
		
		virtual bool checked() = 0;
		virtual void setChecked(bool b) = 0;
	};
}