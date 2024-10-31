#pragma once
#include "main.h"
#define BULLET_MAX (10)

// 前方宣言
class Camera;
class Bullet;

class BulletManager final
{
private:
	Bullet* m_Bullet[BULLET_MAX] = {nullptr};	// 弾

	int m_ShotSound = 0;						// ショット時のサウンド
	float m_CurrentCoolTime = 0.0f;				// クールタイムの現在の時間

public:
	~BulletManager();
	void Init();
	void Unit();
	void Update(const float& deltaTime);
	void Draw(const XMFLOAT2& pos);
	bool SpawnBullet(const XMFLOAT2& pos);	// 弾の発射
};