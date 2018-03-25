#pragma once

#include "Engine/Scenegraph/GameScene.h"
#include "Engine/Memory/ObjectPool.h"
#include "Game/Gameplay/Objects/Wall.h"
class GameTime;
class PacmanActor;
class GhostActor;
class FPSObject;

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
	FPSObject* m_pFPS;

	ObjectPool<Wall> m_WallPool;
};

