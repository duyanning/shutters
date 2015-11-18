#pragma once

#include "NativeWindowCreator.hpp"

namespace ShuttersImpl {
	using namespace Shutters;

	class NativeListBoxCreator : public NativeWindowCreator {
	public:
		HWND create();
	};
}
