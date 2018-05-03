#pragma once

#include <thread>
#include <atomic>
#include <functional>

class Thread
{
public:
	Thread();
	~Thread();

	void Start();
	void Stop();
	bool IsFinished() const;
	void AddTask(const std::function<void()>& task);

private:
	void Run();

	std::vector<std::function<void()>> m_Tasks;
	std::atomic<bool> m_IsRunning;
	std::atomic<bool> m_IsFinished;
	std::thread m_Thread;
};