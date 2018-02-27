#pragma once

#include <string>
#include <thread>
#include <mutex>

class Console
{
public:
	Console();

	~Console();

	bool isLineAvailable();

	std::string getLine();

	void print(const std::string& text);

protected:

	void _printConsoleStartOfLine() const;

	void _printConsoleNewLine() const;

	void _finishLine();

	void _mainLoop();

	bool _isStopSignaled;

	std::string _line;
	std::string _buffer;

	std::thread _readerThread;
	std::mutex  _mutex;
};
