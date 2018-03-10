#pragma once

#include "Engine/Scenegraph/GameScene.h"
class RectangleObject;

class TestScene : public GameScene
{
public:
	TestScene();
	virtual ~TestScene();

protected:
	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;

private:
	RectangleObject* m_pRect;
};

