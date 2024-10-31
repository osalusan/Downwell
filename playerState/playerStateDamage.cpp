#include "playerStateDamage.h"
#include "manager/inputManager.h"

constexpr float m_NO_OPERATION_MAX = 0.24f;											// 操作不能時間
constexpr float m_RESISTANT = SCREEN_HEIGET * 0.035f;;								// 抵抗力
constexpr XMFLOAT2 m_INIT_SPEED = { SCREEN_WIDTH * 0.2f ,SCREEN_HEIGET * 0.7f };	// 初速度

void PlayerStateDamage::Init()
{
	m_State = "被ダメ状態";
	if (m_Player != nullptr)
	{
		m_Player->StartInvTime();
		CollisionComponent* Collision = m_Player->GetCollisionComponent();
		if (Collision == nullptr) return;

		m_HitDirectionSide = Collision->GetHitSide();
		m_HitDirectionVertical = Collision->GetHitVertical();

		ImpactSpeedDecision();
		m_Player->InitGravityAcceleration();
	}
	if (m_Texture == TEXTURE::NONE)
	{
		LoadTexture(TEXTURE::PLAYER, "asset\\texture\\T_Player.png");
	}
}

void PlayerStateDamage::Unit()
{
	m_CurrentTime = 0.0f;
	m_Acceleration = { 0.0f,0.0f };
	m_HitDirectionSide = HITDIRECTION::NONE;
	m_HitDirectionVertical = HITDIRECTION::NONE;
}

void PlayerStateDamage::Update(const float& deltaTime)
{
	m_Player->SetVelocityY(m_Player->GetVelocity().y + m_Acceleration.y);
	m_Acceleration.y += m_RESISTANT;

	if (m_Acceleration.x != 0)
	{
		m_Player->SetVelocityX(m_Player->GetVelocity().x + m_Acceleration.x);
		m_Acceleration.x += m_RESISTANT;
	}

	ChangeState();
	m_CurrentTime += deltaTime;
}

void PlayerStateDamage::ChangeState()
{
	if (m_CurrentTime >= m_NO_OPERATION_MAX)
	{
		ChangePlayerState(PLAYERSTATE::IDLE);
	}
	if (m_Player != nullptr)
	{
		if (m_Player->GetHealth() <= 0)
		{
			ChangePlayerState(PLAYERSTATE::DEAD);
		}
	}
}

// ----------------------------------- private -----------------------------------
void PlayerStateDamage::ImpactSpeedDecision()
{
	// 縦と横の吹っ飛び数値を設定
	if (m_HitDirectionSide != HITDIRECTION::NONE)
	{
		if (m_HitDirectionSide == HITDIRECTION::LEFT)
		{
			m_Acceleration.x = m_INIT_SPEED.x;
		}
		else if (m_HitDirectionSide == HITDIRECTION::RIGHT)
		{
			m_Acceleration.x = -m_INIT_SPEED.x;
		}
	}

	m_Acceleration.y = -m_INIT_SPEED.y;
}
