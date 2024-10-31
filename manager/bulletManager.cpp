#include "manager/bulletManager.h"
#include "character/player.h"
#include "manager/sceneManager.h"
#include "object/bullet.h"
#include "map.h"
#include "manager/soundManager.h"

constexpr float m_BULLET_COOLTIME = 0.09f;		// ���̃o���b�g�����Ă�܂�

BulletManager::~BulletManager()
{
	// �e�̍폜
	for (int i = 0; i < BULLET_MAX; i++)
	{
		delete m_Bullet[i];
		m_Bullet[i] = nullptr;
	}
}

void BulletManager::Init()
{
	// �e�̐���
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (m_Bullet[i] == nullptr)
		{
			m_Bullet[i] = new Bullet;
		}

		if (m_Bullet[i] != nullptr)
		{
			m_Bullet[i]->Init();
		}
	}

	SoundManager::ReservSound(SOUND::SHOT, "asset\\sound\\S_Shot.mp3");
}
void BulletManager::Unit()
{
	// �e�̏I������
	for (Bullet* BulletObject : m_Bullet)
	{
		if (BulletObject != nullptr)
		{
			BulletObject->Unit();
		}
	}
}

void BulletManager::Update(const float& deltaTime)
{
	// �e�̍X�V
	for (Bullet* BulletObject : m_Bullet)
	{
		if (BulletObject != nullptr)
		{
			// �����������玟��
			if (!BulletObject->GetEnable()) continue;

			BulletObject->Update(deltaTime);
		}
	}
	m_CurrentCoolTime += deltaTime;
}

void BulletManager::Draw(const XMFLOAT2& pos)
{
	// �e�̕`��
	for (Bullet* BulletObject : m_Bullet)
	{
		if (BulletObject != nullptr)
		{
			// �����������玟��
			if (!BulletObject->GetEnable()) continue;

			BulletObject->Draw(pos);
		}
	}
}

bool BulletManager::SpawnBullet(const XMFLOAT2& pos)
{
	// �e�̐���
	for (Bullet* BulletObject : m_Bullet)
	{
		if (BulletObject != nullptr)
		{
			// �e�̃N�[���^�C��
			if (m_CurrentCoolTime < m_BULLET_COOLTIME) return false;

			if (!BulletObject->GetEnable())
			{
				BulletObject->SetBullet(pos);
				m_CurrentCoolTime = 0.0f;
			
				PlaySoundMem(SoundManager::GetSound(SOUND::SHOT), DX_PLAYTYPE_BACK, true);
				
				return true;
			}
		}
	}
	return false;
}

