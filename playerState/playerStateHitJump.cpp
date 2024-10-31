#include "playerStateHitJump.h"

constexpr float m_HITJUMP_MAX_TIME = 0.15f;				// Å‘åŽžŠÔ
constexpr float m_INIT_SPEED = SCREEN_HEIGET * 0.6f;	// ‰‘¬“x
constexpr float m_RESISTANT = SCREEN_HEIGET * 0.035f;	// ’ïR—Í

void PlayerStateHitJump::Init()
{
	if (m_Player != nullptr)
	{
		m_Player->InitGravityAcceleration();
	}
	m_Acceleration.y = m_INIT_SPEED;

	if (m_Texture == TEXTURE::NONE)
	{
		LoadTexture(TEXTURE::PLAYER_JUMP, "asset\\texture\\T_Player.png");
	}
	m_State = "ƒWƒƒƒ“ƒvUŒ‚ó‘Ô";
	m_CurrentTime = 0.0f;
}

void PlayerStateHitJump::Unit()
{
	m_CurrentTime = 0.0f;
	m_State = "";
}

void PlayerStateHitJump::Update(const float& deltaTime)
{
	if (m_Player != nullptr)
	{
		// ƒWƒƒƒ“ƒv—Í‚ª‚OˆÈ‰º‚¾‚Æ
		if (m_Acceleration.y > 0)
		{
			m_Player->SetVelocityY(m_Player->GetVelocity().y - m_Acceleration.y);
			m_Acceleration.y -= m_RESISTANT;
		}
		else
		{
			m_Acceleration.y = 0;
		}
	}

	m_CurrentTime += deltaTime;
	ChangeState();
}

void PlayerStateHitJump::ChangeState()
{
	// ƒXƒe[ƒg‘JˆÚ / —Dæ“x‡

	if (m_CurrentTime >= m_HITJUMP_MAX_TIME)
	{
		ChangePlayerState(PLAYERSTATE::IDLE);
	}
}

