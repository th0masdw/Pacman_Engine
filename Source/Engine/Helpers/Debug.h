#pragma once

class Debug
{
public:
	static void Initialize();

	static void Log(const std::string& message);
	static void LogWarning(const std::string& warning);
	static void LogError(const std::string& error);
	static void LogFormat(const char* message, ...);

private:
	Debug() = default;
	~Debug() = default;

	static HANDLE m_ConsoleHandle;
	static int m_Padding;
	static const size_t m_ConvertBufferSize = 1024;
	static char m_ConvertBuffer[m_ConvertBufferSize];
};