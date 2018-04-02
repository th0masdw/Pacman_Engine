#pragma once

#include "Engine/Components/CharacterController.h"
class PacmanActor;

class PacmanController : public CharacterController
{
public:
	explicit PacmanController(PacmanActor* pActor, float speed);
	virtual ~PacmanController() = default;

	virtual void CheckCollision(const glm::vec2& direction) override;

private:
	PacmanActor* m_pPlayer;

	void GetHit();
	void EatPellet(GameObject* pPellet);
	void EatPowerPellet(GameObject* pPower);
	void EatFruit(GameObject* pFruit);
};