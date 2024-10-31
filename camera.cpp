#include "camera.h"
#include "character/player.h"
#include "scene/scene.h"
#include "manager/sceneManager.h"
#include "map.h"

// カメラの初期座標
constexpr float m_INIT_POS_Y = SCREEN_HEIGET * 0.15f;

Camera::~Camera()
{
	m_Player = nullptr;
}

void Camera::Init()
{
	m_Position.y = m_INIT_POS_Y;

	// プレイヤーのポインタを保存
	if (m_Player == nullptr)
	{
		Scene* Scene = SceneManager::GetScene();
		if (Scene == nullptr) return;

		Map* Map = Scene->GetMap();
		if (Map == nullptr) return;

		m_Player = Map->GetPlayer();
	}
}

void Camera::Unit()
{
	// GameObjectの純粋仮想関数の為空実装
}

void Camera::Update(const float& deltaTime)
{
	if (m_Player != nullptr)
	{
		m_Position.y -= m_Player->GetVelocity().y;
	}
}


