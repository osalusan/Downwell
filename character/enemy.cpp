#include "enemy.h"

Enemy::Enemy()
{
	m_Enable = true;
}

void Enemy::TakeDamage(const int& atk)
{
	m_Health -= atk;
	if (m_Health <= 0)
	{
		Disable();
	}
}

void Enemy::SetEnemyPos(const XMFLOAT2& pos)
{
	m_Position = pos;
	Init();
}
