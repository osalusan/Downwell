#pragma once
#include "main.h"
#include <vector>

// �O���錾
class Player;

class UI final
{
private:
	Player* m_Player = nullptr;				// �v���C���[�̃|�C���^�ۑ��p

	XMFLOAT2 m_BulletPosition = {};			// ���W
	XMFLOAT2 m_BulletScale = {};			// �傫��
public:
	~UI();
	void Init();
	void Draw();
};