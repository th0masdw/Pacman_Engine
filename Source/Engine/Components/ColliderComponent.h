#pragma once

#include "BaseComponent.h"
#include "Engine/Helpers/Structs.h"

class ColliderComponent : public BaseComponent
{
public:
	explicit ColliderComponent(float width = 1.0f, float height = 1.0f, bool isStatic = true);
	virtual ~ColliderComponent() = default;

	void SetDimensions(float width, float height);
	Rect GetShape() const;
	bool IsStatic() const;

	ColliderComponent(const ColliderComponent& other) = delete;
	ColliderComponent(ColliderComponent&& other) = delete;
	ColliderComponent& operator=(const ColliderComponent& other) = delete;
	ColliderComponent& operator=(ColliderComponent&& other) = delete;

protected:
	virtual void PostInitialize() override;
	virtual void Update(const GameTime& time) override;
	virtual void Draw() const override;

private:
	Rect m_Box;
	bool m_IsStatic;
};