#pragma once

#include "RootWindow.hpp"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

namespace Shutters {
	using namespace std;


	class MdiChildWindow;
	class MenuBar;
	class SubMenu;

	class MdiFrameWindow : public RootWindow {
		typedef RootWindow Base;
	public:
//		MdiFrameWindow(RootWindow* owner = 0);
		MdiFrameWindow();
		~MdiFrameWindow();

		template <class MDICHILD> MDICHILD* newChild();
		void deleteChild(MdiChildWindow* child);
		void setMdiMenu(MenuBar* menuBar, SubMenu* windowMenu);
		void setMdiMenu(MenuBar& menuBar, SubMenu* windowMenu);
		MdiChildWindow* getActiveChild();


	protected:
		virtual void wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result);
	private:
		friend class MdiChildWindow;
		// helper functions
		HWND createChild();
		void destroyChild(HWND child);
		void setMdiMenu(HMENU hMenuBar, HMENU hWindowMenu);

		HWND m_hwndClient;
	};

	template <class MDICHILD>
	MDICHILD*
	MdiFrameWindow::newChild()
	{
		MDICHILD* child = new MDICHILD(this);

		// because we can not receive WM_ACTIVATE when being created,
		// so call it.
		child->onActivate(true);

		return child;
	}

}
