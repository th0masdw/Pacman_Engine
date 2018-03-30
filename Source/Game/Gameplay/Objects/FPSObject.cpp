#include "MiniginPCH.h"
#include "FPSObject.h"
#include "Engine/Helpers/GameTime.h"
#include "Engine/Components/TextComponent.h"

FPSObject::FPSObject(const std::string& fontFile, unsigned int fontSize, const Color& color)
	: GameObject(Tag::Empty, Layer::UI),
	m_pTextComponent(nullptr),
	m_Color(color)
{
	m_pTextComponent = new TextComponent("FPS", color, fontFile, fontSize);
	AddComponent(m_pTextComponent);
}

void FPSObject::Update(const GameTime& time)
{
	m_pTextComponent->SetText(std::to_string(time.GetFPS()), m_Color);
}

void FPSObject::SetColor(const Color& color)
{
	m_Color = color;
}