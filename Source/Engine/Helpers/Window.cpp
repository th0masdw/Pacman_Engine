#include "MiniginPCH.h"
#include "Window.h"

int Window::m_Width{ 775 };
int Window::m_Height{ 775 };
std::string Window::m_Name{ "Programming IV Assignment" };

int Window::GetWidth()
{
	return m_Width;
}

int Window::GetHeight()
{
	return m_Height;
}

std::string Window::GetName()
{
	return m_Name;
}