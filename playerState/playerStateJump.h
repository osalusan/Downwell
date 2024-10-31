#pragma once
#include "playerState.h"

// 前方宣言
class BulletManager;

class PlayerStateJump :public PlayerState
{
private:
	float m_JumpCurrentTime = 0.0f;
	int m_NoAmmoSound = 0;									// 弾切れ時のサウンド
	bool m_IsNoAmmoSound = false;								// 弾切れ音を出したかどうか
	BulletManager* m_BulletManager = nullptr;				// バレットマネージャー保存用

	void ShotBullet();
public:
	using PlayerState::PlayerState;
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
	virtual void ChangeState()override;
};