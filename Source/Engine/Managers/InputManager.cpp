#include "MiniginPCH.h"
#include "InputManager.h"
#include "SceneManager.h"
#include <sstream>
#include <iomanip>

bool InputManager::Update() 
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			return false;

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			SceneManager::GetInstance().NextScene();
			Debug::Log("Next scene");
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			SceneManager::GetInstance().PreviousScene();
			Debug::Log("Previous scene");
		}

		if (GetAsyncKeyState(VK_F4) & 0x8000) {
			Debug::EnableDebugRendering(!Debug::IsDebugRenderingEnabled());
			std::stringstream ss;
			ss << "Debug rendering: " << std::boolalpha << Debug::IsDebugRenderingEnabled();
			Debug::Log(ss.str());
		}
	}
	return true;
}

void InputManager::AddInputAction(const InputAction& action) 
{
	auto it = m_InputActions.find(int(action.id));

	if(it == m_InputActions.end())
		m_InputActions[int(action.id)] = action;
}

bool InputManager::IsActionTriggered(const Input id) 
{
	auto it = m_InputActions.find(int(id));

	if (it != m_InputActions.end()) {
		if (it->second.useGamepad)
			return m_CurrentState.Gamepad.wButtons & it->second.bitMask;
		else
			return m_pKeyboard[it->second.bitMask];		
	}
	return false;
}