#include "MiniginPCH.h"
#include "ScoreManager.h"
#include "Engine/Components/TextComponent.h"
#include "Engine/Managers/EventManager.h"

ScoreManager::ScoreManager()
	: GameObject(Tag::Empty, Layer::UI),
	m_Score(0)
{
	m_pText = new TextComponent("0", { 255, 255, 255, 255 }, "../Resources/Lingua.otf", 20);
	AddComponent(m_pText);

	//Events
	EventManager::GetInstance().StartListening("EatPellet", "EatPelletCB", [this]() { UpdateScore(10); });
	EventManager::GetInstance().StartListening("EatPower", "EatPowerCB", [this]() { UpdateScore(50); });
	EventManager::GetInstance().StartListening("EatFruit", "EatFruitCB", [this]() { UpdateScore(100); });
}

ScoreManager::~ScoreManager()
{
	EventManager::GetInstance().StopListening("EatPellet", "EatPelletCB", [this]() { UpdateScore(10); });
	EventManager::GetInstance().StopListening("EatPower", "EatPowerCB", [this]() { UpdateScore(50); });
	EventManager::GetInstance().StopListening("EatFruit", "EatFruitCB", [this]() { UpdateScore(100); });
}

void ScoreManager::UpdateScore(int amount)
{
	m_Score += amount;
	m_pText->SetText(std::to_string(m_Score), { 255, 255, 255, 255 });
}