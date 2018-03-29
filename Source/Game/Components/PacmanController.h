#pragma once

#include "Engine/Components/CharacterController.h"

class PacmanController : public CharacterController
{
public:
	explicit PacmanController(float speed);
	virtual ~PacmanController() = default;

	virtual void CheckCollision(const glm::vec2& direction) override;
};