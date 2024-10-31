#pragma once
#include "main.h"
#include <vector>

// 前方宣言
class Player;

class UI final
{
private:
	Player* m_Player = nullptr;				// プレイヤーのポインタ保存用

	XMFLOAT2 m_BulletPosition = {};			// 座標
	XMFLOAT2 m_BulletScale = {};			// 大きさ
public:
	~UI();
	void Init();
	void Draw();
};