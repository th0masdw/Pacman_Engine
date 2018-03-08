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
	for(Scene* pScene : m_Scenes)
	{
		pScene->Update(deltaTime);
	}
}

void SceneManager::Draw()
{
	for (Scene* pScene : m_Scenes)
	{
		pScene->Draw();
	}
}

Scene& SceneManager::CreateScene(const string& name)
{
	Scene* pScene = new Scene(name);
	m_Scenes.push_back(pScene);
	return *pScene;
}
