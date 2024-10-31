#pragma once
#include "gameObject.h"

class CollisionComponent;

class Character :public GameObject
{
protected:
	CollisionComponent* m_Collision = nullptr;		// �����蔻��̃R���|�[�l���g
	XMFLOAT2 m_Velocity = {};						// ���x
	XMFLOAT2 m_RecordPosition = {};					// �ߋ����W
	int m_Health = 0;								// �̗�
	int m_Damage = 0;								// �^����_���[�W
	bool m_EnableGravity = false;					// �d�̗͂L�薳��
	float m_GravityAcceleration = 0;				// �d�͉����x
	float m_GravityValue = 0.0f;					// �d��

	const int m_HITOBJECT_COUNT_MIN = 2;			// ���������I�u�W�F�N�g�̍Œᐔ

protected:
	// �q�N���X�Ŏg���֐�
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
	// �擾�͂ł��邪�ύX�͂ł��Ȃ��悤��
	CollisionComponent* GetCollisionComponent()const
	{
		return m_Collision;
	}
	// �̗͂̎擾
	const int& GetHealth()const
	{
		return m_Health;
	}

	// �d�͉����x�̏�����
	void InitGravityAcceleration();
};