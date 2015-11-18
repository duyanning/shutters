#ifndef SHUTTERS_HPP
#define SHUTTERS_HPP

namespace Shutters
{
	class RootWindow;
	class Form;

	void SetStartupWindow(RootWindow* startupWnd);
	void SetStartupWindow(RootWindow& startupWnd);

	void SetStartupWindow(Form* startupWnd);
	void SetStartupWindow(Form& startupWnd);
};

#ifdef _DEBUG
#pragma comment(lib, "Shutters_d")
#else
#pragma comment(lib, "Shutters")
#endif

#endif
