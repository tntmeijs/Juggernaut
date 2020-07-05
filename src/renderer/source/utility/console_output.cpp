#include "utility/console_output.hpp"

#if _WINDOWS
#include <Windows.h>
#endif

#include <iostream>

using namespace jnt;

void ConsoleOutput::Info(std::string_view message)
{
	SetConsoleColor(ConsoleOutput::Color::White);
	std::cout << "[INFO]\t\t" << message << std::endl;
}

void ConsoleOutput::Success(std::string_view message)
{
	SetConsoleColor(ConsoleOutput::Color::Green);
	std::cout << "[SUCCESS]\t"<< message << std::endl;
}

void ConsoleOutput::Warning(std::string_view message)
{
	SetConsoleColor(ConsoleOutput::Color::Yellow);
	std::cout << "[WARNING]\t" << message << std::endl;
}

void ConsoleOutput::Error(std::string_view message)
{
	SetConsoleColor(ConsoleOutput::Color::Red);
	std::cout << "[ERROR]\t\t" << message << std::endl;
}

void ConsoleOutput::Reset()
{
	SetConsoleColor(Color::White);
}

void ConsoleOutput::SetConsoleColor(Color color)
{
#if _WINDOWS
	// Defaults to white
	WORD textColor = 7;
	
	// Any other color besides white
	switch (color)
	{
		case jnt::ConsoleOutput::Color::Green:
			textColor = 10;
			break;
		case jnt::ConsoleOutput::Color::Yellow:
			textColor = 14;
			break;
		case jnt::ConsoleOutput::Color::Red:
			textColor = 12;
			break;
	}

	// Set the new console color
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, textColor);
#else
	color; // Suppress "unreferenced formal parameter"
#endif
}
