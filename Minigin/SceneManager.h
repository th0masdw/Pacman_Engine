#pragma once
#include "Singleton.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene& CreateScene(const std::string& name);
	void Destroy();

	void Update(float deltaTime);
	void Draw();

private:
	std::vector<Scene*> m_Scenes;
};