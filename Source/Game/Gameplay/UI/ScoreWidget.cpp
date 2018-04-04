#include "MiniginPCH.h"
#include "ScoreWidget.h"
#include "Engine/Components/TextComponent.h"
#include "Engine/Managers/EventManager.h"

ScoreWidget::ScoreWidget()
	: GameObject(Tag::Empty, Layer::UI),
	m_Score(0)
{
	m_pText = new TextComponent("0", { 255, 255, 255, 255 }, "../Resources/Lingua.otf", 20);
	AddComponent(m_pText);

	//Events
	EventManager::GetInstance().StartListening("EatPellet", "EatPelletUICB", [this]() { UpdateScore(10); });
	EventManager::GetInstance().StartListening("EatPower", "EatPowerUICB", [this]() { UpdateScore(50); });
	EventManager::GetInstance().StartListening("EatFruit", "EatFruitUICB", [this]() { UpdateScore(100); });
	EventManager::GetInstance().StartListening("EatGhost", "EatGhostUICB", [this]() { UpdateScore(200); });
}

void ScoreWidget::UpdateScore(int amount)
{
	m_Score += amount;
	m_pText->SetText(std::to_string(m_Score), { 255, 255, 255, 255 });
}