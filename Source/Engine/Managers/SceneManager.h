#pragma once
#include "Engine/Helpers/Singleton.h"

class GameScene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	void CreateScene(GameScene* pScene);
	void Destroy();

	void Update(float deltaTime);
	void Draw();

	void SetActiveScene(const std::string& name);
	void NextScene();
	void PreviousScene();

private:
	std::vector<GameScene*> m_Scenes;
	int m_ActiveSceneIndex = -1;
};