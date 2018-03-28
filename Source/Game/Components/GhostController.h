#pragma once

#include "Engine/Components/CharacterController.h"

class GhostController : public CharacterController
{
public:
	explicit GhostController(float speed);
	virtual ~GhostController() = default;

	virtual void CheckCollision(const glm::vec2& direction) override;
};