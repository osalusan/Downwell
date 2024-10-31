#pragma once
#include "character.h"
class Enemy :public Character
{
public:
	Enemy();

	// ダメージを受ける
	virtual void TakeDamage(const int& atk)override;

	// エネミーを有効にする時に使用
	void SetEnemyPos(const XMFLOAT2& pos);
};