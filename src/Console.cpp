#include "Console.hpp"

#include <iostream>
#include <Windows.h>
#include <conio.h>


Console::Console()
{
	_isStopSignaled = false;
	_readerThread = std::thread(&Console::_mainLoop, this);
}

Console::~Console()
{
	_isStopSignaled = true;
	_readerThread.join();
}

bool Console::isLineAvailable()
{
	_mutex.lock();
	bool isEmpty = _line.empty();
	_mutex.unlock();

	return !isEmpty;
}

std::string Console::getLine()
{
	_mutex.lock();

	std::string str = _line;
	_line.clear();
	_mutex.unlock();

	return str;
}

void Console::_mainLoop()
{
	static HANDLE stdinHandle;
	// Get the IO handles
	// getc(stdin);
	stdinHandle = GetStdHandle(STD_INPUT_HANDLE);

	INPUT_RECORD r[512];
	DWORD read;

	_printConsoleStartOfLine();

	while (!_isStopSignaled)
	{
		switch (WaitForSingleObject(stdinHandle, 1000))
		{
		case(WAIT_TIMEOUT):
			break; // return from this function to allow thread to terminate
		case(WAIT_OBJECT_0):
			if (_kbhit()) // _kbhit() always returns immediately
			{
				const char i = _getch();

				if (i == '\r')
				{
					_finishLine();
					_printConsoleNewLine();
					_printConsoleStartOfLine();
				}
				else
				{
					putc(i, stdout);
					_buffer.push_back(i);
				}
			}
			else // some sort of other events , we need to clear it from the queue
			{
				// clear events
				ReadConsoleInput(stdinHandle, r, 512, &read);
			}
			break;
		case(WAIT_FAILED):
			std::cerr << "WAIT_FAILED" << std::endl;
			break;
		case(WAIT_ABANDONED):
			std::cerr << "WAIT_ABANDONED" << std::endl;
			break;
		default:
			std::cerr << "Someting's unexpected was returned.";
		}
	}
}

void Console::_finishLine()
{
	_mutex.lock();

	_line.clear();
	_line.insert(_line.end(), _buffer.begin(), _buffer.end());
	_buffer.clear();

	_mutex.unlock();
}

void Console::_printConsoleStartOfLine() const
{
	std::cout << "> ";
}

void Console::_printConsoleNewLine() const
{
	std::cout << std::endl;
}

void Console::print(const std::string& text)
{
	_mutex.lock();

	_printConsoleNewLine();
	std::cout << text;
	_printConsoleNewLine();
	_printConsoleStartOfLine();

	_mutex.unlock();
}
