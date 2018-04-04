#include "MiniginPCH.h"
#include "LivesWidget.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Managers/EventManager.h"

LivesWidget::LivesWidget()
	: GameObject(Tag::Empty, Layer::UI),
	m_NrLives(4)
{
	for (UINT i = 0; i < m_NrLives; ++i) {
		GameObject* pLife = new GameObject(Tag::Empty, Layer::UI);
		ShapeComponent* pShape = new ShapeComponent(15.0f, 15.0f, { 255, 255, 0, 255 });
		pLife->AddComponent(pShape);
		pLife->GetTransform()->Translate(0.0f, i * -40.0f);
		AddChild(pLife);
		m_pLives.emplace_back(pLife);
	}

	//Events
	EventManager::GetInstance().StartListening("Die", "DieLivesCB", [this]() { UpdateLives(); });
}

void LivesWidget::UpdateLives()
{
	GameObject* pLast = m_pLives.back();
	RemoveChild(pLast);

	m_pLives.pop_back();
}