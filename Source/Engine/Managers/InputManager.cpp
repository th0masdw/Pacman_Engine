#include "MiniginPCH.h"
#include "InputManager.h"
#include "SceneManager.h"
#include <SDL.h>

bool InputManager::Update() {
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			SceneManager::GetInstance().NextScene();
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			SceneManager::GetInstance().PreviousScene();
		}
	}
	return true;
}

void InputManager::AddInputAction(const InputAction& action) {
	auto it = m_InputActions.find(int(action.id));

	if(it == m_InputActions.end())
		m_InputActions[int(action.id)] = action;
}

bool InputManager::IsActionTriggered(const Input id) {
	auto it = m_InputActions.find(int(id));

	if (it != m_InputActions.end()) {
		return m_CurrentState.Gamepad.wButtons & it->second.bitMask;	//TODO: add Player 2 support
	}
	return false;
}
