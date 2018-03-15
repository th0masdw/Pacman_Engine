#include "MiniginPCH.h"
#include <iomanip>

HANDLE Debug::m_ConsoleHandle{ nullptr };
int Debug::m_Padding{ 10 };
char Debug::m_ConvertBuffer[] = {};

void Debug::Initialize() 
{
	m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Debug::Log(const std::string& message) 
{
	SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << std::setw(m_Padding) << std::left << "[LOG]" << message;
	std::cout << std::endl;
}

void Debug::LogWarning(const std::string& warning) 
{
	SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	std::cout << std::setw(m_Padding) << std::left << "[WARNING]" << warning;
	std::cout << std::endl;
}

void Debug::LogError(const std::string& error) 
{
	SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED);
	std::cout << std::setw(m_Padding) << std::left << "[ERROR]" << error;
	std::cout << std::endl;
}

void Debug::LogFormat(const char* message, ...) 
{
	va_list ap;
	va_start(ap, message);
	vsnprintf_s(&m_ConvertBuffer[0], m_ConvertBufferSize, m_ConvertBufferSize, message, ap);
	va_end(ap);

	Log(std::string(&m_ConvertBuffer[0]));
}