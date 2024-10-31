#include "object/bullet.h"
#include "scene/scene.h"
#include "manager/sceneManager.h"
#include "camera.h"
#include "object/block.h"
#include "character/enemy.h"
#include "component/boxCollisionComponent.h"

// 初期設定
constexpr XMFLOAT2 m_BULLET_SIZE = { SCREEN_WIDTH * 0.018f,SCREEN_HEIGET * 0.032f };

// 弾の各種設定
constexpr float m_BULLET_SPEED = SCREEN_HEIGET * 0.65f;			// 弾の速度
constexpr float m_BULLET_LIFETIME = 1.0f;						// 弾の生存時間/秒数

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
	// 有効な時
	if (m_Enable)
	{
		if (m_BoxCollision != nullptr)
		{
			m_BoxCollision->Update();
		}
		// 弾の速度設定
		m_Velocity.y = m_BULLET_SPEED * deltaTime;

		// 移動処理
		m_Position.y += m_Velocity.y;

		// 現在の生存時間の経過
		m_CurrentLifeTime += deltaTime;

		// 当たり判定制御
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

// ブロックとの当たり判定制御
void Bullet::CollisionControl()
{
	if (m_BoxCollision != nullptr)
	{
		// ブロックとの当たり判定
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
		// エネミーとの当たり判定
		if (m_BoxCollision->CheckHitCollision(COLLISIONTAG::ENEMY))
		{
			// nullチェック
			Enemy* EnemyObject = m_BoxCollision->GetHitGameObject<Enemy>();
			if (EnemyObject == nullptr) return;

			EnemyObject->TakeDamage(1);

			m_CurrentLifeTime = m_BULLET_LIFETIME;
		}
	}

}
