#pragma once

#include "Engine/Scenegraph/GameObject.h"
class ShapeComponent;

class LivesWidget : public GameObject
{
public:
	LivesWidget();
	virtual ~LivesWidget() = default;

private:
	UINT m_NrLives;
	std::vector<GameObject*> m_pLives;

	void UpdateLives();
};