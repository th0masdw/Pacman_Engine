#pragma once

#include "Engine/Gameplay/Actor.h"
class GameTime;

class PacmanActor final : public Actor
{
public:
	explicit PacmanActor(float width = 1, float height = 1, const Color& color = { 255, 255, 255, 255 }, float speed = 50.0f);
	virtual ~PacmanActor() = default;

	virtual void Update(const GameTime& time) override;

private:
	virtual void Initialize() override;
};