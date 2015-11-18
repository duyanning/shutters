#include <iostream>
#include <shutters/Console.hpp>

using namespace std;
using namespace Shutters;

int main()
{
	Console& console = Console::instance();

	console.setTitle(console.title() + L" Shutters");

	console.setForegroundColor(Console::RED);
	cout << "red\n";
	console.setForegroundColor(Console::DARK_RED);
	cout << "dark red\n";
	console.setForegroundColor(Console::GREEN);
	cout << "green\n";
	console.setForegroundColor(Console::DARK_GREEN);
	cout << "dark green\n";
	console.setForegroundColor(Console::BLUE);
	cout << "blue\n";
	console.setForegroundColor(Console::DARK_BLUE);
	cout << "dark blue\n";
	console.setForegroundColor(Console::YELLOW);
	cout << "yellow\n";
	console.setForegroundColor(Console::DARK_YELLOW);
	cout << "dark yellow\n";
	console.setForegroundColor(Console::CYAN);
	cout << "cyan\n";
	console.setForegroundColor(Console::DARK_CYAN);
	cout << "dark cyan\n";
	console.setForegroundColor(Console::MAGENTA);
	cout << "magenta\n";
	console.setForegroundColor(Console::DARK_MAGENTA);
	cout << "dark magenta\n";
	console.setForegroundColor(Console::BLACK);
	cout << "black\n";
	console.setForegroundColor(Console::WHITE);
	cout << "white\n";
	console.setForegroundColor(Console::GRAY);
	cout << "gray\n";

	console.setBackgroundColor(Console::DARK_BLUE);
	console.setForegroundColor(Console::YELLOW);
	cout << "Hello, world\n";

	console.setCursorPosition(10, 10);
}
