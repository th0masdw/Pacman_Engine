#pragma once

#include "Engine/Scenegraph/GameObject.h"
struct vec2;
class GameTime;
class CharacterController;

class PacmanActor final : public GameObject
{
public:
	explicit PacmanActor(float size = 50.0f, float speed = 50.0f);
	virtual ~PacmanActor() = default;

	void Update(const GameTime& time);
	void Draw() const;
	void LoseLife();
	void PowerUp();

	glm::vec2 GetPosition() const;
	bool IsPowered() const;

private:
	CharacterController* m_pController;
	glm::vec2 m_Direction;
	int m_Lives;
	bool m_IsPowered;
	float m_PoweredTimer;
};