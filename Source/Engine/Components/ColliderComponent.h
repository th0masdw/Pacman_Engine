#pragma once

#include "BaseComponent.h"
class GameTime;

class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent();
	virtual ~ColliderComponent();

	ColliderComponent(const ColliderComponent& other) = delete;
	ColliderComponent(ColliderComponent&& other) = delete;
	ColliderComponent& operator=(const ColliderComponent& other) = delete;
	ColliderComponent& operator=(ColliderComponent&& other) = delete;

protected:
	virtual void Update(const GameTime& time) override;
	virtual void Draw() const override;
};