#pragma once
#include "main.h"
#define BULLET_MAX (10)

// �O���錾
class Camera;
class Bullet;

class BulletManager final
{
private:
	Bullet* m_Bullet[BULLET_MAX] = {nullptr};	// �e

	int m_ShotSound = 0;						// �V���b�g���̃T�E���h
	float m_CurrentCoolTime = 0.0f;				// �N�[���^�C���̌��݂̎���

public:
	~BulletManager();
	void Init();
	void Unit();
	void Update(const float& deltaTime);
	void Draw(const XMFLOAT2& pos);
	bool SpawnBullet(const XMFLOAT2& pos);	// �e�̔���
};