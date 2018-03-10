#include "MiniginPCH.h"
#include "Callback.h"

Callback::Callback(const string& name, const function<void()>& function)
	: m_Name{ name },
	m_Function{ function }
{
}

void Callback::operator()() const {
	m_Function();
}

bool operator==(const Callback& left, const Callback& right) {
	return left.m_Name == right.m_Name;
}

bool operator<(const Callback& left, const Callback& right) {
	return left.m_Name < right.m_Name;
}