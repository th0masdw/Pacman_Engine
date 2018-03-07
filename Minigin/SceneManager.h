#pragma once
#include "Singleton.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene & CreateScene(const std::string& name);

	void Update();
	void Render();

private:
	std::vector<std::shared_ptr<Scene>> m_Scenes;
};