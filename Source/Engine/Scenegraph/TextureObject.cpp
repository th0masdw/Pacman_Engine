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
	Renderer::GetInstance().RenderTexture(*m_Texture, GetPosition().x, GetPosition().y);
}

void TextureObject::SetTexture(const string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}