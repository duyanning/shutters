#pragma once

#include "NativeWindowCreator.hpp"

namespace ShuttersImpl {
	using namespace Shutters;

	class NativeFrameWindowCreator : public NativeWindowCreator {
	public:
		HWND create();
	};
}
