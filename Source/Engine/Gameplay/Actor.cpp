#include "MiniginPCH.h"
#include "Actor.h"

Actor::Actor(float width, float height, const Color& color, float speed)
	: RectangleObject(width, height, color),
	m_Speed{ speed }
{
}

void Actor::SetSpeed(float speed)
{
	m_Speed = speed;
}

void Actor::Move(const Vector2& direction) 
{
	Vector2 flippedDir = { direction.x, direction.y * -1.0f };
	Vector2 pos = GetTransform()->GetPosition();
	pos += flippedDir * m_Speed;
	GetTransform()->Translate(pos);
}