#pragma once

#include "NativeWindowCreator.hpp"

namespace ShuttersImpl {
	using namespace Shutters;

	class NativeButtonCreator : public NativeWindowCreator {
	public:
		HWND create();
	};
}
