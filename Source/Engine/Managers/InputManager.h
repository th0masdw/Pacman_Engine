#pragma once
#include <XInput.h>
#include <SDL.h>
#include "Engine/Helpers/Singleton.h"
#include "Engine/Helpers/Structs.h"
#include <map>

class InputManager final : public Singleton<InputManager>
{
public:
	bool Update();
	void AddInputAction(const InputAction& action);
	bool IsActionTriggered(const Input id);

private:
	static const int m_NrOfPlayers = 2;
	XINPUT_STATE m_GamepadStates[m_NrOfPlayers];

	const Uint8* m_pKeyboard{ SDL_GetKeyboardState(nullptr) };

	std::map<int, InputAction> m_InputActions{};
};