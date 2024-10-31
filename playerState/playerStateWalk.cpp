#include "playerStateWalk.h"
#include "manager/inputManager.h"

void PlayerStateWalk::Init()
{
	m_State = "�������";

	if (m_Texture == TEXTURE::NONE)
	{
		LoadTexture(TEXTURE::PLAYER_WALK, "asset\\texture\\T_Player_Walk.png");
	}
}

void PlayerStateWalk::Unit()
{
	if (m_Player != nullptr)
	{
		m_Player->SetVelocityX(0);
	}
	m_State = "";
}

void PlayerStateWalk::Update(const float& deltaTime)
{
	if (m_Player != nullptr)
	{
		if (InputManager::GetKeyPress(KEY_INPUT_A))
		{
			m_Player->SetVelocityX({ -m_MOVESPEED });
		}
		if (InputManager::GetKeyPress(KEY_INPUT_D))
		{
			m_Player->SetVelocityX({ m_MOVESPEED });
		}
	}
	ChangeState();
}

void PlayerStateWalk::ChangeState()
{
	if (m_Player != nullptr)
	{
		if (!InputManager::GetKeyPress(KEY_INPUT_SPACE))
		{
			m_Player->SetIsJump(false);
		}

		// �X�e�[�g�J�� / �D��x��

		if (m_Player->GetIsDamaged())
		{
			ChangePlayerState(PLAYERSTATE::DAMAGE);		// DamageState��
		}
		else if (m_Player->GetIsAttackEnemy())
		{
			ChangePlayerState(PLAYERSTATE::HITJUMP);	// HitJump��
		}
		else if ((m_Player->GetIsGround() && InputManager::GetKeyPress(KEY_INPUT_SPACE) && !m_Player->GetIsJump()))
		{
			m_Player->SetIsJump(true);
			ChangePlayerState(PLAYERSTATE::JUMP);		// �W�����v�ւ̑J�� / �W�����v��	
		}
		else if (!m_Player->GetIsGround() && m_Player->GetVelocity().y > 0)
		{
			ChangePlayerState(PLAYERSTATE::JUMP);		// �W�����v�ւ̑J�� / ������
		}
		else if (m_Player->GetVelocity().x == 0)
		{
			ChangePlayerState(PLAYERSTATE::IDLE);		// �ҋ@��Ԃ�
		}		
	}
}
