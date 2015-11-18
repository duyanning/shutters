#pragma once

#include "NativeWindowCreator.hpp"

namespace ShuttersImpl {
	using namespace Shutters;

	class NativeChildWindowCreator : public NativeWindowCreator {
	public:
		HWND create();
	};
}
