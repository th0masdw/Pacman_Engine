#pragma once

class Window
{
public:
	static int GetWidth();
	static int GetHeight();
	static std::string GetName();

private:
	Window() = default;
	~Window() = default;

	static int m_Width;
	static int m_Height;
	static std::string m_Name;
};