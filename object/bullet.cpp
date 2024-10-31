#include "object/bullet.h"
#include "scene/scene.h"
#include "manager/sceneManager.h"
#include "camera.h"
#include "object/block.h"
#include "character/enemy.h"
#include "component/boxCollisionComponent.h"

// �����ݒ�
constexpr XMFLOAT2 m_BULLET_SIZE = { SCREEN_WIDTH * 0.018f,SCREEN_HEIGET * 0.032f };

// �e�̊e��ݒ�
constexpr float m_BULLET_SPEED = SCREEN_HEIGET * 0.65f;			// �e�̑��x
constexpr float m_BULLET_LIFETIME = 1.0f;						// �e�̐�������/�b��

Bullet::Bullet()
{
	LoadTexture(TEXTURE::BULLET, "asset\\texture\\T_Bullet.png");
	m_Scale = m_BULLET_SIZE;
	if (m_BoxCollision == nullptr)
	{
		m_BoxCollision = new BoxCollisionComponent(this);
	}
	if (m_BoxCollision != nullptr)
	{
		m_BoxCollision->Init();
		m_BoxCollision->SetCollisionTag(COLLISIONTAG::BULLET);
	}
}

Bullet::~Bullet()
{
	delete m_BoxCollision;
	m_BoxCollision = nullptr;
}

void Bullet::Init()
{
	m_Enable = false;
}

void Bullet::Unit()
{
	if (m_BoxCollision != nullptr)
	{
		m_BoxCollision->Unit();
	}
	m_CurrentLifeTime = 0.0f;
	m_Enable = false;
}

void Bullet::Update(const float& deltaTime)
{
	if (m_CurrentLifeTime >= m_BULLET_LIFETIME)
	{
		Unit();
	}
	// �L���Ȏ�
	if (m_Enable)
	{
		if (m_BoxCollision != nullptr)
		{
			m_BoxCollision->Update();
		}
		// �e�̑��x�ݒ�
		m_Velocity.y = m_BULLET_SPEED * deltaTime;

		// �ړ�����
		m_Position.y += m_Velocity.y;

		// ���݂̐������Ԃ̌o��
		m_CurrentLifeTime += deltaTime;

		// �����蔻�萧��
		CollisionControl();
	}

}

void Bullet::Draw(const XMFLOAT2& cameraPos)
{
	GameObject::Draw(cameraPos);
	if (m_BoxCollision != nullptr)
	{
		m_BoxCollision->Draw();
	}
}

void Bullet::SetBullet(const XMFLOAT2& pos)
{
	if (m_BoxCollision != nullptr)
	{
		m_BoxCollision->Init();
	}
	m_Position = pos;
	m_Enable = true;
}

// �u���b�N�Ƃ̓����蔻�萧��
void Bullet::CollisionControl()
{
	if (m_BoxCollision != nullptr)
	{
		// �u���b�N�Ƃ̓����蔻��
		if (m_BoxCollision->CheckHitCollision(COLLISIONTAG::BLOCK))
		{
			Block* BlockObject = m_BoxCollision->GetHitGameObject<Block>();
			if (BlockObject == nullptr) return;

			if (BlockObject->GetBlockType() == BLOCK::BREAK)
			{
				BlockObject->Disable();
			}

			m_CurrentLifeTime = m_BULLET_LIFETIME;
		}
		// �G�l�~�[�Ƃ̓����蔻��
		if (m_BoxCollision->CheckHitCollision(COLLISIONTAG::ENEMY))
		{
			// null�`�F�b�N
			Enemy* EnemyObject = m_BoxCollision->GetHitGameObject<Enemy>();
			if (EnemyObject == nullptr) return;

			EnemyObject->TakeDamage(1);

			m_CurrentLifeTime = m_BULLET_LIFETIME;
		}
	}

}
