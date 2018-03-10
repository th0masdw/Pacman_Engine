#include "MiniginPCH.h"
#include "GameObject.h"
#include "Engine/Helpers/Structs.h"

GameObject::GameObject(const Vector2& pos)
	: m_Position{ pos }
{
}

void GameObject::SetPosition(const Vector2& pos) {
	m_Position = pos;
}