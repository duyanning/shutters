#pragma once

#include "Window.hpp"



namespace Shutters {


	class NativeWindow : public Window {
		typedef Window Base;
	public:
		NativeWindow();
		~NativeWindow();
	};

}
