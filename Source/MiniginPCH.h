#pragma once

#include "targetver.h"

//#include <stdio.h>
#include <iostream> // std::cout
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "fmod.hpp" //Precompiled Header
#pragma warning(push)
#pragma warning(disable: 4505) //Unreferenced local function removed (FMOD_ErrorString)
#include "fmod_errors.h"
#pragma warning(pop)

#include "Engine/Helpers/Debug.h"
#include "Engine/Helpers/GameTime.h"
#include "Engine/Helpers/HelperFunctions.h"