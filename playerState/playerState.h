#pragma once
#include "character/player.h"
#include <string>

class PlayerState
{
protected:
	Player* m_Player = nullptr;							// 保存用
	const float m_MOVESPEED = SCREEN_WIDTH* 0.16f;		// 移動速度
	XMFLOAT2 m_Acceleration = {};						// 加速度
	std::string m_State = "";							// 現在のStateの文字
	TEXTURE m_Texture = TEXTURE::NONE;					// 読み込んだテクスチャ
public:
	PlayerState(Player* player);
	virtual ~PlayerState();
	void ChangePlayerState(PLAYERSTATE playerState);
	virtual void Init() = 0;
	virtual void Unit() = 0;
	virtual void Update(const float& deltaTime) = 0;
	void Draw();
	void LoadTexture(const TEXTURE& texture, const std::string& fileName);
	virtual void ChangeState() = 0;		// ステートの切り替え処理

	const TEXTURE& GetTexture()
	{
		return m_Texture;
	}
};