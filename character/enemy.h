#pragma once
#include "character.h"
class Enemy :public Character
{
public:
	Enemy();

	// �_���[�W���󂯂�
	virtual void TakeDamage(const int& atk)override;

	// �G�l�~�[��L���ɂ��鎞�Ɏg�p
	void SetEnemyPos(const XMFLOAT2& pos);
};