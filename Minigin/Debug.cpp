#include "MiniginPCH.h"
#include <iomanip>

HANDLE Debug::m_ConsoleHandle{ nullptr };
int Debug::m_Padding{ 10 };
char Debug::m_ConvertBuffer[] = {};

void Debug::Initialize() {
	m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Debug::Log(const string& message) {
	SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << setw(m_Padding) << left << "[LOG]" << message;
	cout << endl;
}

void Debug::LogWarning(const string& warning) {
	SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << setw(m_Padding) << left << "[WARNING]" << warning;
	cout << endl;
}

void Debug::LogError(const string& error) {
	SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << setw(m_Padding) << left << "[ERROR]" << error;
	cout << endl;
}

void Debug::LogFormat(const char* message, ...) {
	va_list ap;
	va_start(ap, message);
	vsnprintf_s(&m_ConvertBuffer[0], m_ConvertBufferSize, m_ConvertBufferSize, message, ap);
	va_end(ap);

	Log(string(&m_ConvertBuffer[0]));
}