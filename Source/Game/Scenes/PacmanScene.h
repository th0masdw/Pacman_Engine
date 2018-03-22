#pragma once

#include "Engine/Scenegraph/GameScene.h"
class GameTime;
class PacmanActor;
class GhostActor;
class Wall;
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
	Wall* m_pWall;
	FPSObject* m_pFPS;
};

