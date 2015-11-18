#pragma once

//#include "Window.hpp"
#include "WinControl.hpp"

namespace Shutters {

	class MdiClient : public WinControl {
		typedef WinControl Base;
	//class MdiClient : public Window {
	//	typedef Window Base;
	public:
		MdiClient();
		~MdiClient();
	};
}
