#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Engine/Scenegraph/Scene.h"

void SceneManager::Destroy() {
	for (Scene* pScene : m_Scenes) {
		delete pScene;
	}
}

void SceneManager::Update(float deltaTime)
{
	for(auto scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void SceneManager::Draw()
{
	for (const auto scene : m_Scenes)
	{
		scene->Draw();
	}
}

Scene& SceneManager::CreateScene(const string& name)
{
	Scene* pScene = new Scene(name);
	m_Scenes.push_back(pScene);
	return *pScene;
}
