#pragma once

#include "NativeWindowCreator.hpp"

namespace ShuttersImpl {
	using namespace Shutters;

	class NativeComboBoxCreator : public NativeWindowCreator {
	public:
		HWND create();
	};
}
