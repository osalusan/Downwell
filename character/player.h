#pragma once
#include "character.h"
class PlayerState;

enum class PLAYERSTATE
{
	NONE = 0,
	IDLE,
	JUMP,
	DAMAGE,
	WALK,
	HITJUMP,
	DEAD,
	MAX
};

class Player final :public Character
{
private:
	PlayerState* m_CurrentPlayerState = nullptr;							// ���݂̃X�e�[�g
	std::unordered_map<PLAYERSTATE, PlayerState*> m_PlayerStatePool = {};	// �X�e�[�g�̕ۑ�

	float m_InvCurrentTime = 0.0f;				// ���G�J�E���g
	bool m_IsGround = false;					// �n�ʂɐG�ꂽ���ǂ���
	bool m_IsDamaged = false;					// �_���[�W���󂯂���
	bool m_IsAttackEnemy = false;				// �G�l�~�[�ɍU������������
	bool m_IsInv = false;						// ���G����
	bool m_IsHead = false;						// ���Ƀu���b�N������������
	bool m_IsJamp = false;						// �W�����v�������Ă��邩�ǂ���

	float m_FlashCurrentTime = 0.0f;			// �_�Ŏ��Ԃ̃J�E���g
	bool m_Flash = false;						// �t���b�V����
	
	int m_PlayerBulletCount = 0;				// �v���C���[�����˂����e

	void HitBlock();				// �u���b�N�Ɠ���������
	void HitEnemy();				// �G�l�~�[�Ɠ���������

	void HitJellyfish(class Jellyfish* jellyfish);

	virtual void MoveControl(const float& deltaTime)override;			// �ړ�����
	virtual void CollisionControl()override;	// �����蔻�萧��

	void FlashControl();

public:
	Player();
	~Player();
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
	virtual void Draw(const XMFLOAT2& cameraPos)override;
	virtual void TakeDamage(const int& atk)override;
	// �v���C���[�̃X�e�[�g���擾
	PlayerState* GetPlayerState()
	{
		return m_CurrentPlayerState;
	}
	// �v���C���[�̃X�e�[�g��ݒ�
	void SetPlayerState(PLAYERSTATE playerState);
	// �e���ˎ��ɌĂ�
	void ShotBullet();

	// ���G���Ԃɓ���
	void StartInvTime()
	{
		m_IsInv = true;
	}
	int GetBulletNumber()const;

	const bool& GetIsGround()const
	{
		return m_IsGround;
	}
	const bool& GetIsDamaged()const
	{
		return m_IsDamaged;
	}
	const bool& GetIsAttackEnemy()const
	{
		return m_IsAttackEnemy;
	}
	const bool& GetIsHead()const
	{
		return m_IsHead;
	}
	void SetIsJump(const bool& jump)
	{
		m_IsJamp = jump;
	}
	const bool& GetIsJump()
	{
		return m_IsJamp;
	}
};