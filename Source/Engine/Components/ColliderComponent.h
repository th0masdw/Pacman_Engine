#pragma once

#include "BaseComponent.h"

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
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;
};