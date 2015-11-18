#pragma once

#include <shutters/Shutters.hpp>
#include <shutters/Button.hpp>
#include <shutters/FrameWindow.hpp>

using namespace Shutters;

class AboutDialog : public FrameWindow {
	Button btnOk;
public:
	AboutDialog();
	void btnOk_click(void*, EventArgs&);
};
