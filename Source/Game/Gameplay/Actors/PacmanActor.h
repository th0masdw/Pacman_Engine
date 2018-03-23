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

	glm::vec2 GetPosition() const;

private:
	CharacterController* m_pController;
	glm::vec2 m_Direction;
};