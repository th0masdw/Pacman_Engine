#pragma once

#include "Engine/Scenegraph/GameObject.h"
class TextComponent;

class ScoreManager : public GameObject
{
public:
	ScoreManager();
	virtual ~ScoreManager();

private:
	int m_Score;
	TextComponent* m_pText;

	void UpdateScore(int amount);
};