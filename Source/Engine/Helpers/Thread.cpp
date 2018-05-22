#include "MiniginPCH.h"
#include "Thread.h"

Thread::Thread()
	: m_Tasks(),
	m_IsRunning(true),
	m_DoWork(false),
	m_Mutex(),
	m_Condition(),
	m_Thread(&Thread::Run, this)
{
}

Thread::~Thread()
{
	if (m_Thread.joinable())
		m_Thread.join();
}

void Thread::Start()
{
	std::lock_guard<std::mutex> guard(m_Mutex);

	m_IsRunning = true;
	m_DoWork = true;

	m_Condition.notify_one();
	
}

void Thread::Stop()
{
	m_IsRunning = false;
}

bool Thread::IsFinished() const
{
	return !m_DoWork;
}

void Thread::AddTask(const std::function<void()>& task)
{
	m_Tasks.push_back(task);
}

void Thread::Run()
{
	while (m_IsRunning) {
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Condition.wait(lock, std::bind(&Thread::m_DoWork, this));

		for (const std::function<void()>& task : m_Tasks) {
			task();
		}

		m_DoWork = false;
	}
}