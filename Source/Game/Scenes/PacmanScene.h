#pragma once

#include "Engine/Scenegraph/GameScene.h"
class GameTime;
class PacmanActor;
class RectangleObject;
class TextComponent;

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
	RectangleObject* m_pWall;

	GameObject* m_pTextureObject;
	GameObject* m_pTextObject;
	TextComponent* m_FPSCounter;
};

