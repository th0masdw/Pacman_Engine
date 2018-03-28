#pragma once

#include "BaseComponent.h"
#include "Engine/Helpers/Structs.h"
#include "Engine/Helpers/Callback.h"
#include <map>
struct vec2;

class CharacterController : public BaseComponent
{
public:
	explicit CharacterController(float speed);
	virtual ~CharacterController() = default;

	void Move(const glm::vec2& direction);
	virtual void CheckCollision(const glm::vec2& direction) = 0;

	CharacterController(const CharacterController& other) = delete;
	CharacterController(CharacterController&& other) = delete;
	CharacterController& operator=(const CharacterController& other) = delete;
	CharacterController& operator=(CharacterController&& other) = delete;

protected:
	virtual void PostInitialize() override;
	virtual void Update(const GameTime& time) override;
	virtual void Draw() const override;

private:
	float m_Speed;
};

