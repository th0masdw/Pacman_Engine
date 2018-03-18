#pragma once

#include "Engine/Scenegraph/GameScene.h"
class GameTime;
class TextComponent;
class PacmanActor;
class GhostActor;
class Wall;

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
	TextComponent* m_pFPSCounter;
	PacmanActor* m_pPlayer;
	GhostActor* m_pGhost;
	Wall* m_pWall;
};

