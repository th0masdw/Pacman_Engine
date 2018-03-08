#include "MiniginPCH.h"
#include "TextureObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

TextureObject::~TextureObject() = default;

void TextureObject::Update(){}

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
