#pragma once

#include "Engine/Gameplay/Actor.h"

class PacmanActor final : public Actor
{
public:
	explicit PacmanActor(const Vector2& pos = {}, float width = 1, float height = 1, 
						 const Color& color = { 255, 255, 255, 255 }, float speed = 50.0f);
	virtual ~PacmanActor() = default;

	virtual void Update(float deltaTime) override;

private:
	virtual void Initialize() override;
};