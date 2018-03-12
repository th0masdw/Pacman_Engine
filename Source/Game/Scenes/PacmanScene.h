#pragma once

#include "Engine/Scenegraph/GameScene.h"
class PacmanActor;
class RectangleObject;

class PacmanScene : public GameScene
{
public:
	PacmanScene();
	virtual ~PacmanScene();

protected:
	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;

private:
	PacmanActor* m_pPlayer;
	RectangleObject* m_pWall;
};

