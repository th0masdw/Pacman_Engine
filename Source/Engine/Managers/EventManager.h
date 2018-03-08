#pragma once

#include "Engine/Helpers/Singleton.h"
#include <map>
#include <functional>

class EventManager final : public Singleton<EventManager>
{
public:
	void Init();

private:
	//std::map<std::string,
};