#include "titleScene.h"
#include "manager/inputManager.h"
#include "manager/sceneManager.h"
#include "scene/gameScene.h"
#include "manager/textureManager.h"

// PushSpaceKey�̏����ݒ�
constexpr XMINT2 m_PUSH_TEXTURE_SIZE = { SCREEN_WIDTH / 3,SCREEN_HEIGET / 4 };
constexpr XMINT2 m_PUSH_TEXTURE_POS = { SCREEN_WIDTH / 2 , SCREEN_HEIGET / 2 + SCREEN_HEIGET / 5 };
constexpr float m_PUSH_MAX_SIZE_VALUE = 0.01f;			// PushSpaceKey�̑傫���̏��

constexpr float m_MOVE_TIME = 1.5f;

void TitleScene::Init()
{
	TextureManager::ReservTexture(TEXTURE::TITLE_DOWNWELL, "asset\\texture\\T_Title_Downwell.png");
	TextureManager::ReservTexture(TEXTURE::PUSHKEY_SPACE, "asset\\texture\\T_PushSpaceKey.png");
	m_CurrentTime = 0.0f;
}
void TitleScene::Unit()
{
	// �������z�֐��̈׉�����
}
void TitleScene::Update()
{
	if (m_CurrentTime >= m_NO_SPACE_KEY_MAX)
	{
		if (InputManager::GetKeyPress(KEY_INPUT_SPACE))
		{
			SceneManager::ChangeScene<GameScene>();
		}
	}

	const float& DeltaTime = GetDeltaTime();

	// �摜�̃T�C�Y�ύX�̐��l��������
	if (m_Up)
	{
		m_MoveValue += DeltaTime;
	}
	else
	{
		m_MoveValue -= DeltaTime;
	}

	if (m_MoveValue >= m_MOVE_TIME)
	{
		m_Up = false;
	}
	else if(m_MoveValue <= 0)
	{
		m_Up = true;
	}

	m_CurrentTime += DeltaTime;
}

void TitleScene::Draw()
{
	DrawExtendGraph(0, 0,SCREEN_WIDTH,SCREEN_HEIGET, TextureManager::GetTexture(TEXTURE::TITLE_DOWNWELL), true);

	const XMINT2& HalfSize = { m_PUSH_TEXTURE_SIZE.x / 2 ,m_PUSH_TEXTURE_SIZE.y / 2};
	const float& SizeValue = m_MoveValue * m_PUSH_MAX_SIZE_VALUE;
	const XMINT2& UpSize = { static_cast<int>(m_MoveValue * (SCREEN_WIDTH * SizeValue)),static_cast<int>(m_MoveValue * (SCREEN_HEIGET * SizeValue)) };
	DrawExtendGraph(m_PUSH_TEXTURE_POS.x - HalfSize.x - UpSize.x, m_PUSH_TEXTURE_POS.y - HalfSize.y - UpSize.y,
		            m_PUSH_TEXTURE_POS.x + HalfSize.x + UpSize.x, m_PUSH_TEXTURE_POS.y + HalfSize.y + UpSize.y, TextureManager::GetTexture(TEXTURE::PUSHKEY_SPACE), true);
}
