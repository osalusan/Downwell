#include "playerStateJump.h"
#include "manager/sceneManager.h"
#include "scene/scene.h"
#include "manager/inputManager.h"
#include "manager/bulletManager.h"
#include "manager/soundManager.h"
#include "map.h"

// �e�푬�x�ݒ�
constexpr float m_INIT_SPEED = SCREEN_HEIGET * 0.7f;			// �����x
constexpr float m_RESISTANT = SCREEN_HEIGET * 0.035f;			// ��R��
constexpr float m_JUMP_TIME = 0.7f;								// �������W�����v����
constexpr float m_FORCE = SCREEN_HEIGET * 0.021f;				// �������W�����v���̗�

void PlayerStateJump::Init()
{
	m_State = "�W�����v���";
	m_JumpCurrentTime = 0;
	if (m_Player != nullptr)
	{
		// �W�����v���ɏ����x��ݒ�
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
		// �������W�����v
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
		// �e�̔���
		else if (m_JumpCurrentTime > m_JUMP_TIME)
		{
			ShotBullet();
		}
		
		if (m_Player->GetIsHead())
		{
			m_JumpCurrentTime = m_JUMP_TIME;
			m_Acceleration.y = 0.0f;
		}

		// �W�����v���̈ړ�
		if (InputManager::GetKeyPress(KEY_INPUT_A))
		{
			m_Player->SetVelocityX({ -m_MOVESPEED });
		}
		if (InputManager::GetKeyPress(KEY_INPUT_D))
		{
			m_Player->SetVelocityX({ m_MOVESPEED });
		}

		// �W�����v�͂�0�ȏゾ��
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
		// �X�e�[�g�J�� / �D��x��

		if (m_Player->GetIsDamaged())
		{
			ChangePlayerState(PLAYERSTATE::DAMAGE);		// DamageState��
		}
		else if (m_Player->GetIsAttackEnemy())
		{
			ChangePlayerState(PLAYERSTATE::HITJUMP);	// HitJump��
		}	
		else if (m_Player->GetIsGround() && m_JumpCurrentTime > 1)
		{
			ChangePlayerState(PLAYERSTATE::IDLE);		// �ҋ@��Ԃ� / �n�ʂɒ��n������A�W�����v�����u�Ԃɔ������Ȃ��悤��
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

			// BulletManager�̊i�[
			if (m_BulletManager == nullptr)
			{
				// null�`�F�b�N
				Scene* Scene = SceneManager::GetScene();
				if (Scene == nullptr) return;

				Map* Map = Scene->GetMap();
				if (Map == nullptr) return;

				BulletManager* BulletManager = Map->GetBulletManager();
				m_BulletManager = BulletManager;
			}

			if (m_BulletManager == nullptr) return;

			// �c�e��������������
			if (m_Player->GetBulletNumber() <= 0)
			{
				if (m_IsNoAmmoSound)
				{
					PlaySoundMem(SoundManager::GetSound(SOUND::NOAMMO), DX_PLAYTYPE_BACK, m_IsNoAmmoSound);
				}
				m_IsNoAmmoSound = false;
				return;
			}

			// �e�̔��˂�����������
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