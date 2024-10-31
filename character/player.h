#pragma once
#include "character.h"
class PlayerState;

enum class PLAYERSTATE
{
	NONE = 0,
	IDLE,
	JUMP,
	DAMAGE,
	WALK,
	HITJUMP,
	DEAD,
	MAX
};

class Player final :public Character
{
private:
	PlayerState* m_CurrentPlayerState = nullptr;							// 現在のステート
	std::unordered_map<PLAYERSTATE, PlayerState*> m_PlayerStatePool = {};	// ステートの保存

	float m_InvCurrentTime = 0.0f;				// 無敵カウント
	bool m_IsGround = false;					// 地面に触れたかどうか
	bool m_IsDamaged = false;					// ダメージを受けた時
	bool m_IsAttackEnemy = false;				// エネミーに攻撃成功した時
	bool m_IsInv = false;						// 無敵時間
	bool m_IsHead = false;						// 頭にブロックが当たった時
	bool m_IsJamp = false;						// ジャンプし続けているかどうか

	float m_FlashCurrentTime = 0.0f;			// 点滅時間のカウント
	bool m_Flash = false;						// フラッシュ中
	
	int m_PlayerBulletCount = 0;				// プレイヤーが発射した弾

	void HitBlock();				// ブロックと当たった後
	void HitEnemy();				// エネミーと当たった後

	void HitJellyfish(class Jellyfish* jellyfish);

	virtual void MoveControl(const float& deltaTime)override;			// 移動制御
	virtual void CollisionControl()override;	// 当たり判定制御

	void FlashControl();

public:
	Player();
	~Player();
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
	virtual void Draw(const XMFLOAT2& cameraPos)override;
	virtual void TakeDamage(const int& atk)override;
	// プレイヤーのステートを取得
	PlayerState* GetPlayerState()
	{
		return m_CurrentPlayerState;
	}
	// プレイヤーのステートを設定
	void SetPlayerState(PLAYERSTATE playerState);
	// 弾発射時に呼ぶ
	void ShotBullet();

	// 無敵時間に入る
	void StartInvTime()
	{
		m_IsInv = true;
	}
	int GetBulletNumber()const;

	const bool& GetIsGround()const
	{
		return m_IsGround;
	}
	const bool& GetIsDamaged()const
	{
		return m_IsDamaged;
	}
	const bool& GetIsAttackEnemy()const
	{
		return m_IsAttackEnemy;
	}
	const bool& GetIsHead()const
	{
		return m_IsHead;
	}
	void SetIsJump(const bool& jump)
	{
		m_IsJamp = jump;
	}
	const bool& GetIsJump()
	{
		return m_IsJamp;
	}
};