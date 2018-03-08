#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Structs.h"
#include <map>

class InputManager final : public Singleton<InputManager>
{
public:
	bool Update();
	void AddInputAction(const InputAction& action);
	bool IsActionTriggered(const Input id);

private:
	XINPUT_STATE m_CurrentState{};	//TODO: add second state for player 2

	std::map<int, InputAction> m_InputActions{};
};