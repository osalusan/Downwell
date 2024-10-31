#pragma once
#include "playerState.h"
#include "component/collisionConponent.h"

class PlayerStateDead :public PlayerState
{
private:
	float m_CurrentTime = 0.0f;									// ����s�\�J�E���g

	HITDIRECTION m_HitDirectionSide = HITDIRECTION::NONE;
	HITDIRECTION m_HitDirectionVertical = HITDIRECTION::NONE;

public:
	using PlayerState::PlayerState;
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
	virtual void ChangeState()override;
};