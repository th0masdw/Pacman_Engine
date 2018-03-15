#pragma once

#include "Engine/Scenegraph/GameObject.h"
class GameTime;

class PacmanActor final : public GameObject
{
public:
	explicit PacmanActor(float size, float speed);
	virtual ~PacmanActor() = default;

	void Update(const GameTime& time);
	void Draw() const;

	void SetSize(float size);
	void SetSpeed(float speed);

private:
	float m_Speed;
	
	void Move(const Vector2& displacement);
};