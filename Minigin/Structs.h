#pragma once

#include "MiniginPCH.h"

struct WindowSettings
{
	WindowSettings()
		: Width(640),
		Height(480),
		Name("Programming IV Assignment")
	{
	}

	int Width;
	int Height;
	std::string Name;
};