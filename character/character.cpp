#include "character.h"
#include "scene/scene.h"
#include "manager/sceneManager.h"
#include "camera.h"
#include "component/boxCollisionComponent.h"
#include "map.h"

constexpr float m_FALL_SPEED_MAX = SCREEN_HEIGET * 1.15f;			// 落下の最高速度

Character::~Character()
{
	delete m_Collision; 
	m_Collision = nullptr;
}

void Character::Init()
{
	if (m_Collision == nullptr)
	{
		m_Collision = new BoxCollisionComponent(this);
	}
	if (m_Collision != nullptr)
	{
		m_Collision->Init();
	}
	m_Enable = true;
}

void Character::Unit()
{
	m_Velocity = { 0.0f,0.0f };
	if (m_Collision != nullptr)
	{
		m_Collision->Unit();
	}
	Disable();
}

void Character::Update(const float& deltaTime)
{
	// 移動値の初期化
	m_Velocity.x = 0;

	// 重力
	if (m_EnableGravity)
	{
		m_GravityAcceleration += m_GravityValue * deltaTime;
		// 落下速度上限
		if (m_GravityAcceleration >= m_FALL_SPEED_MAX)
		{
			m_GravityAcceleration = m_FALL_SPEED_MAX;
		}
		m_Velocity.y += m_GravityAcceleration;
	}

	// 移動処理
	MoveControl(deltaTime);

	m_Velocity.y *= deltaTime;
	m_Velocity.x *= deltaTime;

	m_Position.x += m_Velocity.x;
	m_Position.y += m_Velocity.y;

	if (m_Collision != nullptr)
	{
		m_Collision->Update();
	}

	// 当たり判定処理
	CollisionControl();

	// プレイヤーの横移動制限
	const float& HarfScaleX = m_Scale.x * 0.5f;
	if (m_Position.x - HarfScaleX <= LEFT_WALL)
	{
		m_Position.x = LEFT_WALL + HarfScaleX;
	}
	else if (m_Position.x + HarfScaleX >= RIGHT_WALL)
	{
		m_Position.x = RIGHT_WALL - HarfScaleX;
	}

	// 過去座標の保存
	m_RecordPosition = m_Position;
}

void Character::Draw(const XMFLOAT2& cameraPos)
{
	GameObject::Draw(cameraPos);
	if (m_Collision != nullptr)
	{
		m_Collision->Draw();
	}
}

void Character::InitGravityAcceleration()
{
	m_GravityAcceleration = 0.0f;
}
