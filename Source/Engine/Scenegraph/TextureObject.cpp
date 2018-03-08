#include "MiniginPCH.h"
#include "TextureObject.h"
#include "Engine/Managers/ResourceManager.h"
#include "Engine/Graphics/Renderer.h"

TextureObject::~TextureObject() = default;

void TextureObject::Update(float deltaTime) {
	UNREFERENCED_PARAMETER(deltaTime);
}

void TextureObject::Draw() const
{
	auto pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void TextureObject::SetTexture(const string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
