#pragma once

#include "wincpp.hpp"

namespace Shutters {

	class GdiplusManager {
	public:
		GdiplusManager();
		~GdiplusManager();
	private:
		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartupInput gdiplusStarupInput;
	};

}
