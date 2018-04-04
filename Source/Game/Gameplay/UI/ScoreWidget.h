#pragma once

#include "Engine/Scenegraph/GameObject.h"
class TextComponent;

class ScoreWidget : public GameObject
{
public:
	ScoreWidget();
	virtual ~ScoreWidget() = default;

private:
	int m_Score;
	TextComponent* m_pText;

	void UpdateScore(int amount);
};