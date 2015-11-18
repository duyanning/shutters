#pragma once

#include "Window.hpp"
#include "CancelEvent.hpp"
#include "Event.hpp"
#include "DialogResult.hpp"


namespace Shutters {

	class MenuBar;
	class EventArgs;
	class MdiClient;
	class Icon;

	// Form is superseded by RootWindow, perhaps we should rename RootWindow to Form
	class Form : public Window {
		typedef Window Base;
	public:
		Form();
		~Form();
		void dispose();

		MenuBar* menu();
		void setMenu(MenuBar* menuBar);
		void setMenu(MenuBar& menuBar);

		Form* getOwner();
		void close();
		DialogResult showDialog(Form* owner = 0);

		bool isMdiContainer();
		void setIsMdiContainer(bool is);


		// read only
		bool isMdiChild();

		Form* mdiParent();
		void setMdiParent(Form* p);
		// event
		CancelEvent closing;
		Event closed;
		Event load;

		// property
		void setIcon(Icon* icon);
		Icon* getIcon();
	protected:
		virtual void wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result);
		DialogResult dialogResult;
		virtual void onClosing(CancelEventArgs& e);
		virtual void onClosed(EventArgs& e);
		virtual void onLoad(EventArgs& e);
		virtual void onMdiChildActivate(EventArgs& e);
	private:
		void disposeSelf();	// non-virtual
		MenuBar* m_menuBar;

		Form* m_owner;
		bool m_isModal;
		bool m_isMdiContainer;
		bool m_isMdiChild;

		MdiClient* m_mdiClient;
		HWND m_hwndClient;
		//Form* m_mdiParent;

		// mdi child stuffs
		bool m_ourMenuBar;
	};

}
