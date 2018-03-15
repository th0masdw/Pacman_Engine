#include "MiniginPCH.h"
#include "EventManager.h"

void EventManager::Init() 
{
	m_Events.clear();
}

void EventManager::StartListening(const std::string& eventName, const std::string& callbackName, const std::function<void()>& callback) 
{
	auto it = m_Events.find(eventName);

	if (it != m_Events.end()) {
		it->second.AddListener(Callback{ callbackName, callback });
	} else {
		Event newEvent{};
		newEvent.AddListener(Callback{ callbackName, callback });
		m_Events[eventName] = newEvent;
	}
}

void EventManager::StopListening(const std::string& eventName, const std::string& callbackName, const std::function<void()>& callback) 
{
	auto it = m_Events.find(eventName);

	if (it != m_Events.end())
		it->second.RemoveListener(Callback{ callbackName, callback });
}

void EventManager::TriggerEvent(const std::string& eventName) 
{
	auto it = m_Events.find(eventName);

	if (it != m_Events.end())
		it->second.Invoke();
}