#include "playerStateWalk.h"
#include "manager/inputManager.h"

void PlayerStateWalk::Init()
{
	m_State = "歩き状態";

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

		// ステート遷移 / 優先度順

		if (m_Player->GetIsDamaged())
		{
			ChangePlayerState(PLAYERSTATE::DAMAGE);		// DamageStateへ
		}
		else if (m_Player->GetIsAttackEnemy())
		{
			ChangePlayerState(PLAYERSTATE::HITJUMP);	// HitJumpへ
		}
		else if ((m_Player->GetIsGround() && InputManager::GetKeyPress(KEY_INPUT_SPACE) && !m_Player->GetIsJump()))
		{
			m_Player->SetIsJump(true);
			ChangePlayerState(PLAYERSTATE::JUMP);		// ジャンプへの遷移 / ジャンプ時	
		}
		else if (!m_Player->GetIsGround() && m_Player->GetVelocity().y > 0)
		{
			ChangePlayerState(PLAYERSTATE::JUMP);		// ジャンプへの遷移 / 落下時
		}
		else if (m_Player->GetVelocity().x == 0)
		{
			ChangePlayerState(PLAYERSTATE::IDLE);		// 待機状態へ
		}		
	}
}
