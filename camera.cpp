#include "camera.h"
#include "character/player.h"
#include "scene/scene.h"
#include "manager/sceneManager.h"
#include "map.h"

// �J�����̏������W
constexpr float m_INIT_POS_Y = SCREEN_HEIGET * 0.15f;

Camera::~Camera()
{
	m_Player = nullptr;
}

void Camera::Init()
{
	m_Position.y = m_INIT_POS_Y;

	// �v���C���[�̃|�C���^��ۑ�
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
	// GameObject�̏������z�֐��̈׋����
}

void Camera::Update(const float& deltaTime)
{
	if (m_Player != nullptr)
	{
		m_Position.y -= m_Player->GetVelocity().y;
	}
}


