#pragma once
#include "gameObject.h"

// �O���錾
class BoxCollisionComponent;

class Bullet :public GameObject
{
private:
	BoxCollisionComponent* m_BoxCollision = nullptr;
	float m_CurrentLifeTime = 0;					// ���݂̐�������

	XMFLOAT2 m_Velocity = {};						// ���x

public:
	Bullet();
	~Bullet();
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
	virtual void Draw(const XMFLOAT2& cameraPos)override;
	void SetBullet(const XMFLOAT2& pos);
	void CollisionControl();
};