#include "wincpp.hpp"

#include "Console.hpp"


using namespace Shutters;

//Console&
//Shutters::console()
//{
//	static Console c;
//	return c;
//}

Console&
Console::instance()
{
	static Console c;
	return c;
}

Console::Console()
{
}

Console::~Console()
{
}

wstring
Console::title()
{
	vector<wchar_t> t(MAX_PATH);
	::GetConsoleTitle(&t[0], t.size());
	return &t[0];
}

void
Console::setTitle(const wstring& title)
{
	::SetConsoleTitle(title.c_str());
}

int
Console::cursorLeft()
{
	return 0;
}

int
Console::cursorTop()
{
	return 0;
}

void
Console::setCursorLeft(int left)
{
}

void
Console::setCursorTop(int top)
{
}

void
Console::setCursorPosition(int left, int top)
{
	COORD cursorPos;
	cursorPos.X = left;
	cursorPos.Y	 = top;
	::SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
}

Console::Color
Console::foregroundColor()
{
	return RED;
}

void
Console::setForegroundColor(Color color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	::GetConsoleScreenBufferInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &info);
	WORD attrib = info.wAttributes;
	attrib &= ~(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (color) {
	case RED:
		attrib |= FOREGROUND_INTENSITY;
	case DARK_RED:
		attrib |= FOREGROUND_RED;
		break;
	case GREEN:
		attrib |= FOREGROUND_INTENSITY;
	case DARK_GREEN:
		attrib |= FOREGROUND_GREEN;
		break;
	case BLUE:
		attrib |= FOREGROUND_INTENSITY;
	case DARK_BLUE:
		attrib |= FOREGROUND_BLUE;
		break;

	case YELLOW:
		attrib |= FOREGROUND_INTENSITY;
	case DARK_YELLOW:
		attrib |= FOREGROUND_RED | FOREGROUND_GREEN;
		break;
	case CYAN:
		attrib |= FOREGROUND_INTENSITY;
	case DARK_CYAN:
		attrib |= FOREGROUND_BLUE | FOREGROUND_GREEN;
		break;
	case MAGENTA:
		attrib |= FOREGROUND_INTENSITY;
	case DARK_MAGENTA:
		attrib |= FOREGROUND_RED | FOREGROUND_BLUE;
		break;

	case BLACK:
		break;
	case WHITE:
		attrib |= FOREGROUND_INTENSITY;
		break;
	case GRAY:
		attrib |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	}
	::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), attrib);
}

Console::Color
Console::BackgroundColor()
{
	return RED;
}

void
Console::setBackgroundColor(Color color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	::GetConsoleScreenBufferInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &info);
	WORD attrib = info.wAttributes;
	attrib &= ~(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

	switch (color) {
	case RED:
		attrib |= BACKGROUND_INTENSITY;
	case DARK_RED:
		attrib |= BACKGROUND_RED;
		break;
	case GREEN:
		attrib |= BACKGROUND_INTENSITY;
	case DARK_GREEN:
		attrib |= BACKGROUND_GREEN;
		break;
	case BLUE:
		attrib |= BACKGROUND_INTENSITY;
	case DARK_BLUE:
		attrib |= BACKGROUND_BLUE;
		break;

	case YELLOW:
		attrib |= BACKGROUND_INTENSITY;
	case DARK_YELLOW:
		attrib |= BACKGROUND_RED | BACKGROUND_GREEN;
		break;
	case CYAN:
		attrib |= BACKGROUND_INTENSITY;
	case DARK_CYAN:
		attrib |= BACKGROUND_BLUE | BACKGROUND_GREEN;
		break;
	case MAGENTA:
		attrib |= BACKGROUND_INTENSITY;
	case DARK_MAGENTA:
		attrib |= BACKGROUND_RED | BACKGROUND_BLUE;
		break;

	case BLACK:
		break;
	case WHITE:
		attrib |= BACKGROUND_INTENSITY;
		break;
	case GRAY:
		attrib |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	}
	::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), attrib);
}
