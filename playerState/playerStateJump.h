#pragma once
#include "playerState.h"

// �O���錾
class BulletManager;

class PlayerStateJump :public PlayerState
{
private:
	float m_JumpCurrentTime = 0.0f;
	int m_NoAmmoSound = 0;									// �e�؂ꎞ�̃T�E���h
	bool m_IsNoAmmoSound = false;								// �e�؂ꉹ���o�������ǂ���
	BulletManager* m_BulletManager = nullptr;				// �o���b�g�}�l�[�W���[�ۑ��p

	void ShotBullet();
public:
	using PlayerState::PlayerState;
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
	virtual void ChangeState()override;
};