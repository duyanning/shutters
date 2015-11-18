#pragma once

#include "NativeWindowCreator.hpp"

namespace ShuttersImpl {
	using namespace Shutters;

	class NativeLabelCreator : public NativeWindowCreator {
	public:
		HWND create();
	};
}
