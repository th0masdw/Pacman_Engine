#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void SceneManager::Update()
{
	for(auto scene : m_Scenes)
	{
		scene->Update();
	}
}

void SceneManager::Draw()
{
	for (const auto scene : m_Scenes)
	{
		scene->Draw();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
