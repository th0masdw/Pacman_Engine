#pragma once

#include "Engine/Components/CharacterController.h"
class GhostActor;

class GhostController : public CharacterController
{
public:
	explicit GhostController(GhostActor* pGhost, float speed);
	virtual ~GhostController() = default;

	virtual void CheckCollision(const glm::vec2& direction) override;

private:
	GhostActor* m_pGhost;

	void GetHit();
};