#include "MiniginPCH.h"
#include "Thread.h"

Thread::Thread()
	: m_Tasks(),
	m_IsRunning(true),
	m_IsFinished(false),
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
	m_IsRunning = true;
	m_IsFinished = false;
}

void Thread::Stop()
{
	m_IsRunning = false;
}

bool Thread::IsFinished() const
{
	return m_IsFinished;
}

void Thread::AddTask(const std::function<void()>& task)
{
	m_Tasks.push_back(task);
}

void Thread::Run()
{
	while (m_IsRunning) {
		if (!m_IsFinished) {
			for (const std::function<void()>& task : m_Tasks) {
				task();
			}

			m_IsFinished = true;
		}
	}
}