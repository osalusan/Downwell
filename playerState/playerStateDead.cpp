#include "playerStateDead.h"

constexpr float m_DEAD_TIME = 1.24f;												// €–S‘O‰‰oŠÔ
constexpr float m_RESISTANT = SCREEN_HEIGET * 0.035f;;								// ’ïR—Í
constexpr XMFLOAT2 m_INIT_SPEED = { SCREEN_WIDTH * 0.2f ,SCREEN_HEIGET * 0.7f };	// ‰‘¬“x

void PlayerStateDead::Init()
{
	m_State = "€–Só‘Ô";
	if (m_Player != nullptr)
	{
		CollisionComponent* Collision = m_Player->GetCollisionComponent();
		if (Collision == nullptr) return;

		m_HitDirectionSide = Collision->GetHitSide();
		m_HitDirectionVertical = Collision->GetHitVertical();

		m_Player->InitGravityAcceleration();
	}

	if (m_Texture == TEXTURE::NONE)
	{
		LoadTexture(TEXTURE::PLAYER_DEAD, "asset\\texture\\T_Player_Dead.png");
	}
}

void PlayerStateDead::Unit()
{
	m_CurrentTime = 0.0f;
}

void PlayerStateDead::Update(const float& deltaTime)
{
	if (m_Player == nullptr) return;

	if (m_CurrentTime >= m_DEAD_TIME)
	{
		if (m_Player->GetEnable())
		{
			m_Player->Unit();
		}
	}
	m_CurrentTime += deltaTime;
}

void PlayerStateDead::ChangeState()
{
	// PlayerState‚Ìƒˆ‰¼‘zŠÖ”‚Ìˆ×‚É‹óÀ‘•
}
