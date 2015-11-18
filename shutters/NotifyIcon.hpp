#pragma once

#include "MouseEvent.hpp"
#include "Event.hpp"
#include "Window.hpp"
#include "ContextMenu.hpp"
#include "NativeWindow.hpp"

namespace Shutters {
	using namespace std;

	class Icon;
	class ContextMenu;

	class NotifyIcon : public Component {
	public:
		NotifyIcon();
		~NotifyIcon();
		void setIcon(Icon* icon);
		void setContextMenu(ContextMenu* menu);
		void setText(const wstring& text);
		void setVisible(bool visible);


		void updateIcon(bool showIconInTray);
		void showContextMenu();
		// events
		MouseEvent mouseDown;
		Event click;

		static const int WM_TRAYMOUSEMESSAGE = WM_USER + 1024;

		void wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result);
	private:

		class NotifyIconNativeWindow : public NativeWindow {
		public:
			NotifyIcon* m_reference;
			void wndProc(UINT message, WPARAM wParam, LPARAM lParam, bool& processed, LRESULT& result);
		};

		static int nextId;
		int m_id;
		Icon* m_icon;
		NotifyIconNativeWindow m_window;
		wstring m_text;
		ContextMenu* m_contextMenu;
		bool m_added;
		bool m_visible;

	};

}
