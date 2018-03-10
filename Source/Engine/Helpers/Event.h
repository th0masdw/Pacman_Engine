#pragma once

#include <set>
#include "Callback.h"

class Event
{
public:
	Event() = default;
	~Event() = default;

	void AddListener(const Callback& callback);
	void RemoveListener(const Callback& callback);
	void Invoke();

	/*Event(const Event& other) = delete;
	Event(Event&& other) = delete;
	Event& operator=(const Event& other) = delete;
	Event& operator=(Event&& other) = delete;*/

private:
	std::set<Callback> m_Listeners;
};