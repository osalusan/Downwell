#pragma once
#include "playerState.h"
#include "component/collisionConponent.h"

class PlayerStateDamage :public PlayerState
{
private:
	float m_CurrentTime = 0.0f;									// 操作不能カウント

	HITDIRECTION m_HitDirectionSide = HITDIRECTION::NONE;
	HITDIRECTION m_HitDirectionVertical = HITDIRECTION::NONE;

	void ImpactSpeedDecision(); // ダメージ時の吹っ飛び速度の決定
public:
	using PlayerState::PlayerState;
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
	virtual void ChangeState()override;
};