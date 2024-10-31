#pragma once
#include "character/enemy.h"
class Jellyfish final :public Enemy
{
private:
	class Player* m_Player = nullptr;			// �v���C���[�̃|�C���^�ۑ��p
	XMFLOAT2 m_Acceleration = { 0.0f,0.0f };

	bool m_MoveReverseX = false;
	bool m_MoveReverseY = false;

	virtual void MoveControl(const float& deltaTime)override;
	virtual void CollisionControl()override;

	void HitBlock();	// Block�ɓ���������
	void HitEnemy();    // Enemy�ɓ���������
public:
	using Enemy::Enemy;
	~Jellyfish();
	virtual void Init()override;
	
};