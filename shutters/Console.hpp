#pragma once

#include "wincpp.hpp"

namespace Shutters {

	using namespace std;

	class Console {
	public:

		enum Color {
			BLACK, WHITE, GRAY,
			RED, GREEN, BLUE,
			DARK_RED, DARK_GREEN, DARK_BLUE,
			YELLOW, CYAN, MAGENTA,
			DARK_YELLOW, DARK_CYAN, DARK_MAGENTA
		};

		static Console& instance();

		int windowLeft();
		void setWindowLeft(int left);

		int windowTop();
		void setWindowTop(int top);

		int windowWidth();
		void setWindowWidth(int width);

		int windowHeight();
		void setWindowHeight(int height);

		wstring title();
		void setTitle(const wstring& title);

		int cursorLeft();
		void setCursorLeft(int left);
		int cursorTop();
		void setCursorTop(int top);
		void setCursorPosition(int left, int top);

		int bufferWidth();
		void setBufferWidth(int width);

		int bufferHeight();
		void setBufferHeight(int height);

		Color foregroundColor();
		void setForegroundColor(Color color);
		Color BackgroundColor();
		void setBackgroundColor(Color color);
	protected:
	private:

		Console();
		~Console();
//		friend Console& console();
		Color m_foregroundColor;
		Color m_backgroundColor;
	};

//	Console& console();

}
