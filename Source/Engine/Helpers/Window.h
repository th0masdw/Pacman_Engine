#pragma once

class Window
{
public:
	static int GetWidth();
	static int GetHeight();
	static int GetGridWidth();
	static int GetGridHeight();
	static std::string GetName();

private:
	Window() = default;
	~Window() = default;

	static int m_Width;
	static int m_Height;
	static int m_GridWidth;
	static int m_GridHeight;
	static std::string m_Name;
};