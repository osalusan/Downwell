#pragma once
#include "playerState.h"
class PlayerStateHitJump :public PlayerState
{
private:
	float m_CurrentTime = 0.0f;					// 時間のカウント用

public:
	using PlayerState::PlayerState;
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
	virtual void ChangeState()override;
};