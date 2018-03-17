#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "Engine/Scenegraph/GameObject.h"

TransformComponent::TransformComponent()
	: m_Position{ 0.0f, 0.0f },
	m_Rotation{ 0.0f },
	m_Scale{ 1.0f, 1.0f }
{
}

void TransformComponent::PostInitialize()
{
}

void TransformComponent::Update(const GameTime& time) 
{
	UNREFERENCED_PARAMETER(time);
}

void TransformComponent::Draw() const 
{
}

void TransformComponent::Translate(float x, float y) 
{
	m_Position.x = x;
	m_Position.y = y;
}

void TransformComponent::Translate(const glm::vec2& pos) 
{
	Translate(pos.x, pos.y);
}

void TransformComponent::Rotate(float angle) 
{
	m_Rotation = angle;
	m_Rotation = WrapAngle(m_Rotation);
}

void TransformComponent::Scale(float x, float y) 
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void TransformComponent::Scale(const glm::vec2& scale) 
{
	Scale(scale.x, scale.y);
}

glm::vec2 TransformComponent::GetPosition() const 
{
	GameObject* pParent = m_pGameObject->GetParent();

	if (pParent)
		return m_Position + pParent->GetTransform()->GetPosition();
	else
		return m_Position;
}

float TransformComponent::GetRotation() const 
{
	return m_Rotation;
}

glm::vec2 TransformComponent::GetScale() const 
{
	return m_Scale;
}