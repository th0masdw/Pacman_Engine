#pragma once

#include "Engine/Helpers/Singleton.h"
#include <map>
#include "Engine/Helpers/Event.h"

class EventManager final : public Singleton<EventManager>
{
public:
	void Init();

	void StartListening(const std::string& eventName, const std::string& callbackName, const std::function<void()>& callback);
	void StopListening(const std::string& eventName, const std::string& callbackName, const std::function<void()>& callback);
	void TriggerEvent(const std::string& eventName);

private:
	std::map<std::string, Event> m_Events;
};