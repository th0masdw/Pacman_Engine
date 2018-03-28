#pragma once

#include "Engine/Scenegraph/GameScene.h"
#include "Engine/Helpers/ObjectPool.h"
#include "Game/Gameplay/Objects/Wall.h"
class GameTime;
class PacmanActor;
class GhostActor;
class Pellet;
class FPSObject;
class LevelLoader;

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
	PacmanActor* m_pPlayer;
	GhostActor* m_pGhost;
	Pellet* m_pPellet;
	FPSObject* m_pFPS;

	ObjectPool<Wall> m_WallPool;
	LevelLoader* m_pLoader;
};

