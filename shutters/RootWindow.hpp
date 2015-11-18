#ifndef SHUTTERS_ROOTWINDOW_HPP
#define SHUTTERS_ROOTWINDOW_HPP

#include "Window.hpp"
#include "CancelEvent.hpp"
#include "Event.hpp"
#include "DialogResult.hpp"

namespace Shutters {

	class MenuBar;
	class EventArgs;

	class RootWindow : public Window {
		typedef Window Base;
	public:
		RootWindow();
		~RootWindow() = 0;
		void dispose();
		void setMenu(MenuBar* menuBar);
		void setMenu(MenuBar& menuBar);

		void activate();


		RootWindow* getOwner();
		void close();
		DialogResult showDialog(RootWindow* owner = 0);
		// event
		CancelEvent closing;
		Event closed;
		Event load;

		// property
	protected:
		virtual void wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result);
		DialogResult dialogResult;
		virtual void onClosing(CancelEventArgs& e);
		virtual void onClosed(EventArgs& e);
		virtual void onLoad(EventArgs& e);
	private:
		void disposeSelf();	// non-virtual
		MenuBar* m_menuBar;

		RootWindow* m_owner;
		bool m_isModal;
	};

}

#endif
