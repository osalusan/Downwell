#include "playerState.h"
#include "manager/inputManager.h"
#include "manager/sceneManager.h"
#include "camera.h"
#include "scene/scene.h"
#include "manager/sceneManager.h"
#include "map.h"

PlayerState::PlayerState(Player* player)
{
	// nullチェック
	if (player != nullptr && m_Player == nullptr)
	{
		m_Player = player;
	}
}

PlayerState::~PlayerState()
{
	m_Player = nullptr;
}

void PlayerState::ChangePlayerState(PLAYERSTATE playerState)
{
	// nullチェック
	if (m_Player != nullptr)
	{
		m_Player->SetPlayerState(playerState);
	}
}
void PlayerState::Draw()
{
#if _DEBUG

	if (m_Player != nullptr)
	{
		// nullチェック
		Scene* Scene = SceneManager::GetScene();
		if (Scene == nullptr) return;

		Map* Map = Scene->GetMap();
		if (Map == nullptr) return;

		Camera* CameraObject = Map->GetCamera();
		if (CameraObject == nullptr) return;

		const XMFLOAT2& PlayerPos = m_Player->GetPos();

		DrawString(static_cast<int>(PlayerPos.x + m_Player->GetScale().x), static_cast<int>(PlayerPos.y + CameraObject->GetPos().y), m_State.c_str(), GetColor(255, 0, 255));
	}

#endif // _DEBUG
}

void PlayerState::LoadTexture(const TEXTURE& texture, const std::string& fileName)
{
	m_Texture = texture;
	TextureManager::ReservTexture(texture, fileName);
}
