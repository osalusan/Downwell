#pragma once
#include "gameObject.h"
// �O���錾
class Player;

class Camera final :public GameObject
{
private:
	Player* m_Player = nullptr;	// �v���C���[�̃|�C���^�ۑ��p

public:
	~Camera();
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
};