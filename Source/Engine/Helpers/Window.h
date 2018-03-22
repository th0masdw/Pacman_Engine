#pragma once

class Window
{
public:
	static int GetWidth();
	static int GetHeight();
	static int GetGridSize();
	static std::string GetName();

private:
	Window() = default;
	~Window() = default;

	static int m_Width;
	static int m_Height;
	static int m_GridSize;
	static std::string m_Name;
};