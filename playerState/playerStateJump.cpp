#include "playerStateJump.h"
#include "manager/sceneManager.h"
#include "scene/scene.h"
#include "manager/inputManager.h"
#include "manager/bulletManager.h"
#include "manager/soundManager.h"
#include "map.h"

// 各種速度設定
constexpr float m_INIT_SPEED = SCREEN_HEIGET * 0.7f;			// 初速度
constexpr float m_RESISTANT = SCREEN_HEIGET * 0.035f;			// 抵抗力
constexpr float m_JUMP_TIME = 0.7f;								// 長押しジャンプ時間
constexpr float m_FORCE = SCREEN_HEIGET * 0.021f;				// 長押しジャンプ時の力

void PlayerStateJump::Init()
{
	m_State = "ジャンプ状態";
	m_JumpCurrentTime = 0;
	if (m_Player != nullptr)
	{
		// ジャンプ時に初速度を設定
		if (m_Player->GetIsGround())
		{
			m_Acceleration.y = m_INIT_SPEED;
		}
		else
		{
			m_JumpCurrentTime = m_JUMP_TIME;
		}
	}

	if (m_Texture == TEXTURE::NONE)
	{
		LoadTexture(TEXTURE::PLAYER_JUMP, "asset\\texture\\T_Player_Jump.png");
	}
	if (m_NoAmmoSound == 0)
	{
		SoundManager::ReservSound(SOUND::NOAMMO, "asset\\sound\\S_NoAmmo.mp3");
	}
}

void PlayerStateJump::Unit()
{
	m_State = "";
	m_Acceleration.y = 0;
	m_JumpCurrentTime = 0;
}

void PlayerStateJump::Update(const float& deltaTime)
{
	if (m_Player != nullptr)
	{
		// 長押しジャンプ
		if (m_JumpCurrentTime < m_JUMP_TIME)
		{
			if (InputManager::GetKeyPress(KEY_INPUT_SPACE))
			{
				m_Acceleration.y += m_FORCE;
				m_Player->InitGravityAcceleration();
				m_Player->SetIsJump(true);
			}
			else
			{
				m_JumpCurrentTime = m_JUMP_TIME;
				m_Player->SetIsJump(false);
			}
		}
		// 弾の発射
		else if (m_JumpCurrentTime > m_JUMP_TIME)
		{
			ShotBullet();
		}
		
		if (m_Player->GetIsHead())
		{
			m_JumpCurrentTime = m_JUMP_TIME;
			m_Acceleration.y = 0.0f;
		}

		// ジャンプ中の移動
		if (InputManager::GetKeyPress(KEY_INPUT_A))
		{
			m_Player->SetVelocityX({ -m_MOVESPEED });
		}
		if (InputManager::GetKeyPress(KEY_INPUT_D))
		{
			m_Player->SetVelocityX({ m_MOVESPEED });
		}

		// ジャンプ力が0以上だと
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
	ChangeState();
	m_JumpCurrentTime += deltaTime;
}

void PlayerStateJump::ChangeState()
{
	if (m_Player != nullptr)
	{
		// ステート遷移 / 優先度順

		if (m_Player->GetIsDamaged())
		{
			ChangePlayerState(PLAYERSTATE::DAMAGE);		// DamageStateへ
		}
		else if (m_Player->GetIsAttackEnemy())
		{
			ChangePlayerState(PLAYERSTATE::HITJUMP);	// HitJumpへ
		}	
		else if (m_Player->GetIsGround() && m_JumpCurrentTime > 1)
		{
			ChangePlayerState(PLAYERSTATE::IDLE);		// 待機状態へ / 地面に着地したら、ジャンプした瞬間に反応しないように
		}
	}
}

// -------------------------- private --------------------------

void PlayerStateJump::ShotBullet()
{
	if (m_Player != nullptr)
	{
		if (InputManager::GetKeyPress(KEY_INPUT_SPACE))
		{
			if (m_Player->GetIsJump()) return;

			// BulletManagerの格納
			if (m_BulletManager == nullptr)
			{
				// nullチェック
				Scene* Scene = SceneManager::GetScene();
				if (Scene == nullptr) return;

				Map* Map = Scene->GetMap();
				if (Map == nullptr) return;

				BulletManager* BulletManager = Map->GetBulletManager();
				m_BulletManager = BulletManager;
			}

			if (m_BulletManager == nullptr) return;

			// 残弾数が無かったら
			if (m_Player->GetBulletNumber() <= 0)
			{
				if (m_IsNoAmmoSound)
				{
					PlaySoundMem(SoundManager::GetSound(SOUND::NOAMMO), DX_PLAYTYPE_BACK, m_IsNoAmmoSound);
				}
				m_IsNoAmmoSound = false;
				return;
			}

			// 弾の発射が成功したら
			if (m_BulletManager->SpawnBullet(m_Player->GetPos()))
			{
				m_Player->ShotBullet();
				m_Acceleration.y = m_FORCE + m_RESISTANT;
				m_IsNoAmmoSound = true;
			}
		}
		else
		{
			m_Player->SetIsJump(false);
		}
	}
}