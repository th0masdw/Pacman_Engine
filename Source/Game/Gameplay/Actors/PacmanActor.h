#pragma once

#include "Engine/Scenegraph/GameObject.h"
struct vec2;
class GameTime;

class PacmanActor final : public GameObject
{
public:
	explicit PacmanActor(float size = 50.0f, float speed = 50.0f);
	virtual ~PacmanActor() = default;

	void Update(const GameTime& time);
	void Draw() const;

	void SetSize(float size);
	void SetSpeed(float speed);

private:
	float m_CurrentSpeed;
	float m_MovementSpeed;
	glm::vec2 m_Direction;
	float m_CollisionOffset;
	
	void Move(const glm::vec2& displacement);
};