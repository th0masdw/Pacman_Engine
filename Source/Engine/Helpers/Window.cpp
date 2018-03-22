#include "MiniginPCH.h"
#include "Window.h"

int Window::m_Width{ 775 };
int Window::m_Height{ 775 };
int Window::m_GridWidth{ 31 };
int Window::m_GridHeight{ 31 };
std::string Window::m_Name{ "Programming IV Assignment" };

int Window::GetWidth()
{
	return m_Width;
}

int Window::GetHeight()
{
	return m_Height;
}

int Window::GetGridWidth()
{
	return m_GridWidth;
}

int Window::GetGridHeight()
{
	return m_GridHeight;
}

std::string Window::GetName()
{
	return m_Name;
}