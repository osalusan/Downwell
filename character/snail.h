#pragma once
#include "character/enemy.h"
#include "map.h"
enum class MOVEDIRECTION
{
	NONE = 0,
	UP,
	DOWN,
	RIGHT,
	LEFT
};
class Snail final :public Enemy
{
private:
	MOVEDIRECTION m_MoveDirection = MOVEDIRECTION::NONE;		// 移動方向
	XMFLOAT2 m_CurrentPos = {};									// 現在のポジションの保存用

	virtual void MoveControl(const float& deltaTime)override;
	virtual void CollisionControl()override;

	void HitBlock();			// Blockに当たった時
	void CheckPreviousBlock();	// 進行方向にブロックがあるかどうか確認

public:
	using Enemy::Enemy;
	virtual void Init()override;
	
};