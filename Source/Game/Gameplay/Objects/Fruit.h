#pragma once

#include "Engine/Scenegraph/GameObject.h"

class Fruit : public GameObject
{
public:
	Fruit();
	virtual ~Fruit() = default;
	
	void Update(const GameTime& time);

private:
	float m_Timer;
	bool m_HasAppeared;
};