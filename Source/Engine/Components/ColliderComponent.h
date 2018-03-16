#pragma once

#include "BaseComponent.h"
#include "Engine/Helpers/Structs.h"
class GameTime;

class ColliderComponent : public BaseComponent
{
public:
	explicit ColliderComponent(float width = 1.0f, float height = 1.0f);
	virtual ~ColliderComponent() = default;

	void SetDimensions(float width, float height);

	ColliderComponent(const ColliderComponent& other) = delete;
	ColliderComponent(ColliderComponent&& other) = delete;
	ColliderComponent& operator=(const ColliderComponent& other) = delete;
	ColliderComponent& operator=(ColliderComponent&& other) = delete;

protected:
	virtual void Update(const GameTime& time) override;
	virtual void Draw() const override;

private:
	Rect m_Box;
};