#pragma once

#include <thread>
#include <functional>
#include <mutex>

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
	bool m_IsRunning;
	bool m_DoWork;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
	std::thread m_Thread;
};