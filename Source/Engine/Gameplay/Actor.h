#pragma once

#include "Engine/Scenegraph/RectangleObject.h"

class Actor : public RectangleObject
{
public:
	explicit Actor(float width = 1, float height = 1, const Color& color = { 255, 255, 255, 255 }, float speed = 50.0f);
	virtual ~Actor() = default;

	virtual void Update(float deltaTime)  = 0;
	void SetSpeed(float speed);

protected:
	float m_Speed;

	virtual void Initialize() = 0;
	void Move(const Vector2& direction);
};