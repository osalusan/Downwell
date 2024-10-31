#pragma once
#include "gameObject.h"
// 前方宣言
class Player;

class Camera final :public GameObject
{
private:
	Player* m_Player = nullptr;	// プレイヤーのポインタ保存用

public:
	~Camera();
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
};