#pragma once

#include "targetver.h"

#include <stdio.h>
#include <iostream> // std::cout
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>
#include <string>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Engine/Helpers/Debug.h"
#include "Engine/Helpers/GameTime.h"
#include "Engine/Helpers/HelperFunctions.h"