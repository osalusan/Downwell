#include "gameScene.h"
#include "camera.h"
#include "ui/ui.h"
#include "map.h"
#include "gameOver.h"
#include "character/player.h"
#include "manager/enemyManager.h"
#include "manager/inputManager.h"
#include "manager/sceneManager.h"
#include "manager/bulletManager.h"
#include "scene/titleScene.h"
#include <vector>

const int m_WALL_SIZE = 10;					// 壁のサイズ
const int m_STAGENO_DEFAULT_POS_Y = 200;	// ステージ番号のY座標

GameScene::~GameScene()
{
	m_PlayerCache = nullptr;
	delete m_GameOver;
	m_GameOver = nullptr;
	delete m_Map;
	m_Map = nullptr;
}
void GameScene::Init()
{
	if (m_Map == nullptr)
	{
		m_Map = new Map;
	}
	if (m_Map != nullptr)
	{
		m_Map->Init();
	}

	if (m_UI == nullptr)
	{
		m_UI = new UI;
	}
	if (m_UI != nullptr)
	{
		m_UI->Init();
	}

	if (m_PlayerCache == nullptr)
	{
		m_PlayerCache = m_Map->GetPlayer();
	}

	if (m_GameOver == nullptr)
	{
		m_GameOver = new GameOver;
	}
	if (m_GameOver != nullptr)
	{
		m_GameOver->Init();
	}

	TextureManager::ReservTexture(TEXTURE::WHITE, "asset\\texture\\T_White.png");
	m_StageNo = 1;
	m_StageNoString = "StageNo." + std::to_string(m_StageNo);
}

void GameScene::Unit()
{
	if (m_Map != nullptr)
	{
		m_Map->Unit();
	}
}

void GameScene::Update()
{
	if (m_Map != nullptr)
	{
		m_Map->Update();
	}

	// 一番最後に配置
	if (m_PlayerCache == nullptr) return;

	if (!m_PlayerCache->GetEnable())
	{
		if (m_GameOver == nullptr) return;

		if (m_GameOver->Update())
		{
			m_ChangeScene = true;
		}
	}
	
}

void GameScene::Draw()
{
	if (m_Map != nullptr)
	{
		m_Map->Draw();
	}

	const int& WallTexture = TextureManager::GetTexture(TEXTURE::WHITE);

	// 壁
	DrawExtendGraph(static_cast<int>(LEFT_WALL - m_WALL_SIZE), 0,
					static_cast<int>(LEFT_WALL), SCREEN_HEIGET, WallTexture, true);
	DrawExtendGraph(static_cast<int>(RIGHT_WALL), 0,
					static_cast<int>(RIGHT_WALL + m_WALL_SIZE), SCREEN_HEIGET, WallTexture, true);

	DrawString(0, m_STAGENO_DEFAULT_POS_Y, m_StageNoString.c_str(), GetColor(255, 255, 255));

	if (m_UI != nullptr)
	{
		m_UI->Draw();
	}

	// ゲームオーバー画面の表示/一番最後に配置
	if (m_PlayerCache == nullptr) return;

#if _DEBUG
	// シーン遷移用のテスト
	if (InputManager::GetKeyPress(KEY_INPUT_0))
	{
		if (m_Map != nullptr)
		{
			m_Map->Init();
		}
	}
#endif 

	// プレイヤーのゴール時にステージの更新
	if (m_PlayerCache->GetPos().y >= m_GoalLine)
	{
		if (m_Map != nullptr)
		{
			m_Map->Init();
		}
		m_PlayerCache->Init();

		if (Camera* CameraObject = m_Map->GetCamera())
		{
			CameraObject->Init();
		}	
		m_StageNo++;
		m_StageNoString = "StageNo." + std::to_string(m_StageNo);
	}

	if (!m_PlayerCache->GetEnable())
	{
		if (m_GameOver != nullptr)
		{
			m_GameOver->Draw();
		}
		ChangeGameOver();
	}
}

// -------------------------------- private --------------------------------
void GameScene::ChangeGameOver()
{
	// シーンの遷移
	if (!m_ChangeScene) return;

	if (m_GameOver == nullptr) return;

	if (m_GameOver->GetRetry())
	{
		SceneManager::ChangeScene<GameScene>();
	}
	else
	{
		SceneManager::ChangeScene<TitleScene>();
	}
}