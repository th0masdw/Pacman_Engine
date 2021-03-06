#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Engine/Scenegraph/GameScene.h"
#include <algorithm>

void SceneManager::Destroy() 
{
	for (GameScene* pScene : m_Scenes) {
		delete pScene;
	}
}

void SceneManager::Update(const GameTime& time)
{
	if (m_ActiveSceneIndex < int(m_Scenes.size()))
		m_Scenes[m_ActiveSceneIndex]->Update(time);
}

void SceneManager::Draw()
{
	if (m_ActiveSceneIndex < int(m_Scenes.size()))
		m_Scenes[m_ActiveSceneIndex]->Draw();
}

void SceneManager::CreateScene(GameScene* pScene)
{
	if (pScene) {
		m_Scenes.push_back(pScene);
		++m_ActiveSceneIndex;
		pScene->PostInitialize();
	}
}

void SceneManager::SetActiveScene(const std::string& name) 
{
	auto it = find_if(m_Scenes.begin(), m_Scenes.end(), [name](GameScene* pScene) {
		return pScene->GetName() == name;
	});

	if (it != m_Scenes.end()) {
		m_ActiveSceneIndex = int(distance(m_Scenes.begin(), it));
	} else {
		m_ActiveSceneIndex = 0;
		Debug::LogError("Scene with name " + name + " does not exist");
	}
}

GameScene* SceneManager::GetActiveScene() const
{
	if (m_ActiveSceneIndex > -1)
		return m_Scenes[m_ActiveSceneIndex];

	return nullptr;
}

void SceneManager::NextScene() 
{
	if (m_ActiveSceneIndex + 1 < int(m_Scenes.size()))
		++m_ActiveSceneIndex;
	else
		m_ActiveSceneIndex = 0;
}

void SceneManager::PreviousScene() 
{
	if (m_ActiveSceneIndex - 1 >= 0)
		--m_ActiveSceneIndex;
	else
		m_ActiveSceneIndex = int(m_Scenes.size() - 1);
}