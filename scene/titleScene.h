#pragma once
#include "scene/scene.h"
#include "main.h"

class TitleScene final :public Scene
{
private:
	float m_MoveValue = 0.0f;
	bool m_Up = false;

	// ゲームシーンから戻ってきたときに、すぐにKeyが反応しない用
	float m_CurrentTime = 0.0f;
	const float& m_NO_SPACE_KEY_MAX = 0.2f;
public:
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update()override;
	virtual void Draw()override;
};