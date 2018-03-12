#include "MiniginPCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent()
	: m_Position{ 0.0f, 0.0f },
	m_Scale{ 1.0f, 1.0f }
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Update(float deltaTime) {
	UNREFERENCED_PARAMETER(deltaTime);
}

void TransformComponent::Draw() const 
{
}

void TransformComponent::Translate(float x, float y) {
	m_Position.x = x;
	m_Position.y = y;
}

void TransformComponent::Translate(const Vector2& pos) {
	Translate(pos.x, pos.y);
}

void TransformComponent::Scale(float x, float y) {
	m_Scale.x = x;
	m_Scale.y = y;
}

void TransformComponent::Scale(const Vector2& scale) {
	Scale(scale.x, scale.y);
}

Vector2 TransformComponent::GetPosition() const {
	return m_Position;
}

Vector2 TransformComponent::GetScale() const {
	return m_Scale;
}