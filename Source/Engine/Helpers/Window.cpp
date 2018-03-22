#include "MiniginPCH.h"
#include "Window.h"

int Window::m_Width{ 775 };
int Window::m_Height{ 775 };
int Window::m_GridSize{ 31 };
std::string Window::m_Name{ "Programming IV Assignment" };

int Window::GetWidth()
{
	return m_Width;
}

int Window::GetHeight()
{
	return m_Height;
}

int Window::GetGridSize()
{
	return m_GridSize;
}

std::string Window::GetName()
{
	return m_Name;
}