#pragma once
#include "playerState.h"
class PlayerStateHitJump :public PlayerState
{
private:
	float m_CurrentTime = 0.0f;					// ���Ԃ̃J�E���g�p

public:
	using PlayerState::PlayerState;
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
	virtual void ChangeState()override;
};