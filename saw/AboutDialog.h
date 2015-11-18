#pragma once

#include <shutters/Shutters.hpp>
#include <shutters/Button.hpp>
#include <shutters/Label.hpp>
#include <shutters/FrameWindow.hpp>

using namespace Shutters;

class AboutDialog : public FrameWindow {
public:
	AboutDialog();
	void btnOk_click(void*, EventArgs&);
private:
	Label copyright;
	Button btnOk;
};
