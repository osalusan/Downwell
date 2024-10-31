#include "playerStateIdle.h"
#include "manager/inputManager.h"

void PlayerStateIdle::Init()
{
	if (m_Player != nullptr)
	{
		m_Player->SetVelocityX(0);
		m_Player->SetIsJump(true);
	}
	m_State = "�ҋ@���";

	if (m_Texture == TEXTURE::NONE)
	{
		LoadTexture(TEXTURE::PLAYER, "asset\\texture\\T_Player.png");
	}
}

void PlayerStateIdle::Unit()
{
	m_State = "";
}

void PlayerStateIdle::Update(const float& deltaTime)
{
	ChangeState();
}

void PlayerStateIdle::ChangeState()
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
			ChangePlayerState(PLAYERSTATE::DAMAGE);		// DamageState�ւ̑J��
		}
		else if (m_Player->GetIsAttackEnemy())
		{
			ChangePlayerState(PLAYERSTATE::HITJUMP);	// HitJump�ւ̑J��
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
		else if (InputManager::GetKeyPress(KEY_INPUT_A) || InputManager::GetKeyPress(KEY_INPUT_D))
		{
			ChangePlayerState(PLAYERSTATE::WALK);		// �ړ��ւ̑J��
		}
	}
}

