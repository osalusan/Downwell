#include "ui.h"
#include "character/player.h"
#include "manager/sceneManager.h"
#include "scene/scene.h"
#include "map.h"

constexpr XMFLOAT2 m_DEFAULT_POS_HP = { 100.0f,30.0f };
constexpr XMFLOAT2 m_SIZE_HP = { SCREEN_WIDTH * 0.045f,SCREEN_HEIGET * 0.08f };
constexpr XMFLOAT2 m_DEFAULT_POS_BULLET = { SCREEN_WIDTH * 0.85f ,SCREEN_HEIGET * 0.9f };
constexpr XMFLOAT2 m_SIZE_BULLET = { SCREEN_WIDTH * 0.09f,SCREEN_HEIGET * 0.08f };

UI::~UI()
{
	m_Player = nullptr;
}

void UI::Init()
{
	// プレイヤーのポインタを保存
	if (m_Player == nullptr)
	{
		Scene* Scene = SceneManager::GetScene();
		if (Scene == nullptr) return;

		Map* Map = Scene->GetMap();
		if (Map == nullptr) return;

		m_Player = Map->GetPlayer();
		if (m_Player == nullptr) return;
	}

	TextureManager::ReservTexture(TEXTURE::UI_HEART, "asset\\texture\\T_Heart.png");
	TextureManager::ReservTexture(TEXTURE::UI_BULLETGAGE, "asset\\texture\\T_BulletGage.png");
}

void UI::Draw()
{
	if (m_Player == nullptr) return;

	const XMFLOAT2& HalfScaleHp = { m_SIZE_HP.x / 2,m_SIZE_HP.y / 2 };
	const XMFLOAT2& HalfScaleBullet = { m_SIZE_BULLET.x / 2,m_SIZE_BULLET.y / 2 };
	const int& Health = m_Player->GetHealth();
	const int& Bullet = m_Player->GetBulletNumber();
	const int& HealthTexture = TextureManager::GetTexture(TEXTURE::UI_HEART);
	const int& BulletTexture = TextureManager::GetTexture(TEXTURE::UI_BULLETGAGE);

	for (int HpCount = 0; HpCount < Health; HpCount++)
	{
		const float& PosX = (m_SIZE_HP.x * HpCount) + m_SIZE_HP.x;
		DrawExtendGraph(static_cast<int>(m_DEFAULT_POS_HP.x - HalfScaleHp.x + PosX), static_cast<int>(m_DEFAULT_POS_HP.y - HalfScaleHp.y),
						static_cast<int>(m_DEFAULT_POS_HP.x + HalfScaleHp.x + PosX), static_cast<int>(m_DEFAULT_POS_HP.y + HalfScaleHp.y), HealthTexture, true);
	}

	for (int BulletCount = 0; BulletCount < Bullet; BulletCount++)
	{
		const float& PosY = (m_SIZE_BULLET.y * BulletCount) + m_SIZE_BULLET.y;
		DrawExtendGraph(static_cast<int>(m_DEFAULT_POS_BULLET.x - HalfScaleBullet.x), static_cast<int>(m_DEFAULT_POS_BULLET.y - HalfScaleBullet.y - PosY),
						static_cast<int>(m_DEFAULT_POS_BULLET.x + HalfScaleBullet.x), static_cast<int>(m_DEFAULT_POS_BULLET.y + HalfScaleBullet.y - PosY), BulletTexture, true);
	}

	const std::string& StringHealth = std::to_string(Health);
	DrawString(static_cast<int>(m_DEFAULT_POS_HP.x), static_cast<int>(m_DEFAULT_POS_HP.y), StringHealth.c_str(), GetColor(255, 255, 255));

	const std::string& StringBullet = std::to_string(Bullet);
	DrawString(static_cast<int>(m_DEFAULT_POS_BULLET.x), static_cast<int>(m_DEFAULT_POS_BULLET.y), StringBullet.c_str(), GetColor(255, 255, 255));
}
