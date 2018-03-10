#pragma once

#include "Engine/Scenegraph/GameScene.h"
class RectangleObject;

class TestScene3 : public GameScene
{
public:
	TestScene3();
	virtual ~TestScene3();

protected:
	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;

private:
	RectangleObject* m_pRect;
};

