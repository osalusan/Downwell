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
	MOVEDIRECTION m_MoveDirection = MOVEDIRECTION::NONE;		// �ړ�����
	XMFLOAT2 m_CurrentPos = {};									// ���݂̃|�W�V�����̕ۑ��p

	virtual void MoveControl(const float& deltaTime)override;
	virtual void CollisionControl()override;

	void HitBlock();			// Block�ɓ���������
	void CheckPreviousBlock();	// �i�s�����Ƀu���b�N�����邩�ǂ����m�F

public:
	using Enemy::Enemy;
	virtual void Init()override;
	
};