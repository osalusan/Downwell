#pragma once
#include "main.h"

class GameOver final
{
private:
	XMFLOAT2 m_SelectArrowPos = { 0.0f,0.0f };
	bool m_Retry = true;

	// �Q�[���I�[�o�[�ɂȂ������ɁA������Key���������Ȃ��p
	float m_GameOverCurrentTime = 0.0f;

public:
	void Init();
	bool Update();
	void Draw();
	const bool& GetRetry()
	{
		return m_Retry;
	}
};