#pragma once

#include "Engine/Scenegraph/GameScene.h"
#include "Engine/Helpers/ObjectPool.h"
#include "Game/Gameplay/Objects/Wall.h"
#include "Game/Gameplay/Objects/Pellet.h"
class GameTime;
class PacmanActor;
class GhostActor;
class FPSObject;
class PowerPellet;
class LevelLoader;
class Fruit;

class PacmanScene : public GameScene
{
public:
	PacmanScene();
	virtual ~PacmanScene();

protected:
	virtual void Initialize() override;
	virtual void Update(const GameTime& time) override;
	virtual void Draw() const override;

private:
	enum class SoundId : int
	{
		Background, Chomp, Fruit, Ghost
	};

	PacmanActor* m_pPlayer;
	std::vector<GhostActor*> m_pGhosts;
	std::vector<PowerPellet*> m_pPowerPellets;
	Fruit* m_pFruit;
	FPSObject* m_pFPS;
	bool m_PauseGame;
	int m_PelletCounter;

	ObjectPool<Wall> m_WallPool;
	ObjectPool<Pellet> m_PelletPool;
	LevelLoader* m_pLoader;

	void LoadSounds();
	void RegisterEvents();
	void ResetLevel();
	void GameOver();
	void CheckIfGameWon();
	void PlaySound(const SoundId id);
};

