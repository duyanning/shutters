#pragma once

#include "NativeWindowCreator.hpp"

namespace ShuttersImpl {
	using namespace Shutters;

	class NativeTextBoxCreator : public NativeWindowCreator {
	public:
		HWND create();
	};
}
