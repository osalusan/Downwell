#pragma once
#include "character/player.h"
#include <string>

class PlayerState
{
protected:
	Player* m_Player = nullptr;							// �ۑ��p
	const float m_MOVESPEED = SCREEN_WIDTH* 0.16f;		// �ړ����x
	XMFLOAT2 m_Acceleration = {};						// �����x
	std::string m_State = "";							// ���݂�State�̕���
	TEXTURE m_Texture = TEXTURE::NONE;					// �ǂݍ��񂾃e�N�X�`��
public:
	PlayerState(Player* player);
	virtual ~PlayerState();
	void ChangePlayerState(PLAYERSTATE playerState);
	virtual void Init() = 0;
	virtual void Unit() = 0;
	virtual void Update(const float& deltaTime) = 0;
	void Draw();
	void LoadTexture(const TEXTURE& texture, const std::string& fileName);
	virtual void ChangeState() = 0;		// �X�e�[�g�̐؂�ւ�����

	const TEXTURE& GetTexture()
	{
		return m_Texture;
	}
};