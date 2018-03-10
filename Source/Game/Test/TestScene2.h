#pragma once

#include "Engine/Scenegraph/GameScene.h"
class RectangleObject;

class TestScene2 : public GameScene
{
public:
	TestScene2();
	virtual ~TestScene2();

protected:
	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;

private:
	RectangleObject* m_pRect;
};

