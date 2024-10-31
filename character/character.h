#pragma once
#include "gameObject.h"

class CollisionComponent;

class Character :public GameObject
{
protected:
	CollisionComponent* m_Collision = nullptr;		// 当たり判定のコンポーネント
	XMFLOAT2 m_Velocity = {};						// 速度
	XMFLOAT2 m_RecordPosition = {};					// 過去座標
	int m_Health = 0;								// 体力
	int m_Damage = 0;								// 与えるダメージ
	bool m_EnableGravity = false;					// 重力の有り無し
	float m_GravityAcceleration = 0;				// 重力加速度
	float m_GravityValue = 0.0f;					// 重力

	const int m_HITOBJECT_COUNT_MIN = 2;			// 当たったオブジェクトの最低数

protected:
	// 子クラスで使う関数
	virtual void MoveControl(const float& deltaTime) = 0;
	virtual void CollisionControl() = 0;
	virtual void TakeDamage(const int& atk) = 0;
public:
	virtual ~Character()override;
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
	virtual void Draw(const XMFLOAT2& cameraPos)override;
	const XMFLOAT2& GetVelocity()const 
	{ 
		return m_Velocity; 
	}
	void SetVelocityX(const float& velocityX)
	{
		m_Velocity.x = velocityX;
	}
	void SetVelocityY(const float& velocityY)
	{
		m_Velocity.y = velocityY;
	}
	// 取得はできるが変更はできないように
	CollisionComponent* GetCollisionComponent()const
	{
		return m_Collision;
	}
	// 体力の取得
	const int& GetHealth()const
	{
		return m_Health;
	}

	// 重力加速度の初期化
	void InitGravityAcceleration();
};