#include "gameOver.h"
#include "manager/inputManager.h"
#include "manager/textureManager.h"
#include "map.h"

// 選択の矢印の初期せてい
constexpr int m_ARROW_SIZE = SCREEN_WIDTH / 10;
constexpr XMFLOAT2 m_ARROW_LEFT_POS = { SCREEN_WIDTH * 0.4f,SCREEN_HEIGET * 0.85f };
constexpr XMFLOAT2 m_ARROW_RIGHT_POS = { SCREEN_WIDTH * 0.62f,SCREEN_HEIGET * 0.85f };

// キーを押せない時間
constexpr float m_NO_SPACE_KEY_MAX = 0.5f;

void GameOver::Init()
{
	m_SelectArrowPos = m_ARROW_LEFT_POS;

	TextureManager::ReservTexture(TEXTURE::GAMEOVER, "asset\\texture\\T_GameOver.png");
	TextureManager::ReservTexture(TEXTURE::GAMEOVER_ARROW, "asset\\texture\\T_SelectArrow.png");

	m_GameOverCurrentTime = 0.0f;
	m_Retry = true;
}

bool GameOver::Update()
{
	if (InputManager::GetKeyPress(KEY_INPUT_A))
	{
		m_SelectArrowPos = m_ARROW_LEFT_POS;
		m_Retry = true;
	}
	else if (InputManager::GetKeyPress(KEY_INPUT_D))
	{
		m_SelectArrowPos = m_ARROW_RIGHT_POS;
		m_Retry = false;
	}

	if (InputManager::GetKeyPress(KEY_INPUT_SPACE))
	{
		if (m_GameOverCurrentTime >= m_NO_SPACE_KEY_MAX)
		{
			return true;
		}
	}

	m_GameOverCurrentTime += GetDeltaTime();

	return false;
}

void GameOver::Draw()
{
	// ゲームオーバー画面の表示
	DrawExtendGraph(static_cast<int>(LEFT_WALL), 0,
					static_cast<int>(RIGHT_WALL), SCREEN_HEIGET, TextureManager::GetTexture(TEXTURE::GAMEOVER), true);
	DrawExtendGraph(static_cast<int>(m_SelectArrowPos.x - m_ARROW_SIZE), static_cast<int>(m_SelectArrowPos.y - m_ARROW_SIZE),
					static_cast<int>(m_SelectArrowPos.x + m_ARROW_SIZE), static_cast<int>(m_SelectArrowPos.y + m_ARROW_SIZE), TextureManager::GetTexture(TEXTURE::GAMEOVER_ARROW), true);
}
