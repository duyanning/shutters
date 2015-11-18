#pragma once

#include <shutters/Shutters.hpp>
#include <shutters/FrameWindow.hpp>
#include <shutters/Point.hpp>
#include <vector>
#include <string>

using namespace Shutters;
using namespace std;

class DTForm : public FrameWindow {
public:
	DTForm();
	~DTForm();
	void addControl(Window* control);
	//wstring type;
	wstring name;
	void setControlName(const wstring& name);

	void save();
private:
	vector<Window*> m_controls;
	Window* m_currentControl;

	void someControl_mouseDown(Window* sender, MouseEventArgs& e);
	void someControl_mouseMove(Window* sender, MouseEventArgs& e);
	void someControl_mouseUp(Window* sender, MouseEventArgs& e);

	void this_mouseDown(Window* sender, MouseEventArgs& e);

	void createSawFiles(string baseSawFileName);
};
