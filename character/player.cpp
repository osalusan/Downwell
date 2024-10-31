#include "character/player.h"
#include "manager/inputManager.h"
#include "main.h"
#include "component/boxCollisionComponent.h"
#include "camera.h"
#include "manager/sceneManager.h"
#include "playerstate/playerState.h"
#include "playerstate/playerStateIdle.h"
#include "playerstate/playerStateWalk.h"
#include "playerstate/playerStateJump.h"
#include "playerstate/playerStateDamage.h"
#include "playerstate/playerStateHitJump.h"
#include "playerState/playerStateDead.h"
#include "character/jellyfish.h"
#include "character/snail.h"
#include "object/block.h"

// 初期設定用変数
constexpr XMFLOAT2 m_POS_DEFAULT = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGET * 0.2f };
constexpr XMFLOAT2 m_SCALE_DEFAULT = { SCREEN_WIDTH * 0.04f,SCREEN_HEIGET * 0.07f };
constexpr int m_HEALTH_DEFAULT = 4;
constexpr float m_GRAVITY_DEFAULT = (SCREEN_HEIGET * 0.95f);

// プレイヤーの各種設定
constexpr int m_PLAYER_ATTACK = 10;				// プレイヤーが踏んだ時の攻撃力
constexpr int m_PLAYER_BULLET_MAX = 10;			// 発射可能な弾の上限数
constexpr float m_INV_TIME = 2.0f;				// 無敵時間
constexpr float m_FLASH_TIME = 0.1f;			// 点滅の間隔

Player::Player()
{
	// 初期体力
	m_Health = m_HEALTH_DEFAULT;
}

Player::~Player()
{
	m_PlayerStatePool.clear();
}

void Player::Init()
{
	Character::Init();
	m_Position = { m_POS_DEFAULT.x,m_POS_DEFAULT.y };
	m_Scale = { m_SCALE_DEFAULT.x ,m_SCALE_DEFAULT.y };

	if (m_PlayerStatePool.size() == 0)
	{
		// 要素上限分リハッシュ
		m_PlayerStatePool.reserve(static_cast<int>(PLAYERSTATE::MAX) - 1);

		m_PlayerStatePool.emplace(PLAYERSTATE::IDLE, new PlayerStateIdle(this));
		m_PlayerStatePool.emplace(PLAYERSTATE::WALK, new PlayerStateWalk(this));
		m_PlayerStatePool.emplace(PLAYERSTATE::JUMP, new PlayerStateJump(this));
		m_PlayerStatePool.emplace(PLAYERSTATE::DAMAGE, new PlayerStateDamage(this));
		m_PlayerStatePool.emplace(PLAYERSTATE::HITJUMP, new PlayerStateHitJump(this));
		m_PlayerStatePool.emplace(PLAYERSTATE::DEAD, new PlayerStateDead(this));
	}

	// 初期化
	for (const std::pair<PLAYERSTATE, PlayerState*>& PlayerState : m_PlayerStatePool)
	{
		m_PlayerStatePool[PlayerState.first]->Init();
	}

	// 重力の設定
	m_GravityValue = m_GRAVITY_DEFAULT;
	m_EnableGravity = true;
	InitGravityAcceleration();

	// nullチェック
	if (m_CurrentPlayerState == nullptr)
	{
		m_CurrentPlayerState = m_PlayerStatePool[PLAYERSTATE::IDLE];
	}
	m_IsJamp = true;
	m_PlayerBulletCount = 0;
	m_IsInv = false;
}

void Player::Unit()
{
	for (const auto& PlayerStatePool : m_PlayerStatePool)
	{
		// nullチェック
		if (PlayerStatePool.second != nullptr)
		{
			PlayerStatePool.second->Unit();
		}
	}
	Character::Unit();
}


void Player::Update(const float& deltaTime)
{
	Character::Update(deltaTime);

	// テクスチャの変更
	if (m_CurrentPlayerState != nullptr)
	{
		m_Texture = m_CurrentPlayerState->GetTexture();
	}

	// 無敵時間
	if (m_IsInv)
	{
		// 無敵時間の終了
		if (m_InvCurrentTime >= m_INV_TIME)
		{
			m_IsInv = false;
			m_InvCurrentTime = 0;
			m_FlashCurrentTime = 0;

			return;
		}
		// フラッシュの制御
		FlashControl();

		// 無敵時間カウント
		m_InvCurrentTime += deltaTime;
		m_FlashCurrentTime += deltaTime;
	}
}

void Player::Draw(const XMFLOAT2& cameraPos)
{
	Character::Draw(cameraPos);
	
#if _DEBUG
	// 文字表示用
	if (m_CurrentPlayerState != nullptr)
	{
		m_CurrentPlayerState->Draw();
	}
#endif
}

void Player::TakeDamage(const int& atk)
{
	if (!m_IsInv)
	{
		m_IsDamaged = true;
		m_Health -= atk;
		m_InvCurrentTime = 0.0f;
	}

	if (m_Health <= 0)
	{
		m_Health = 0;
	}
}

// Stateのセット
void Player::SetPlayerState(PLAYERSTATE playerState)
{
	// 同じステートだったらはじく
	if (m_CurrentPlayerState == m_PlayerStatePool[playerState]) return;

	// 終了処理
	if (m_CurrentPlayerState != nullptr)
	{
		m_CurrentPlayerState->Unit();
	}

	// nullチェック
	if (m_PlayerStatePool[playerState] != nullptr)
	{
		m_CurrentPlayerState = m_PlayerStatePool[playerState];
	}

	// 初期化
	if (m_CurrentPlayerState != nullptr)
	{
		m_CurrentPlayerState->Init();
	}
}
void Player::ShotBullet()
{
	InitGravityAcceleration();
	m_PlayerBulletCount++;
}
int Player::GetBulletNumber() const
{
	return m_PLAYER_BULLET_MAX - m_PlayerBulletCount;
}
void Player::MoveControl(const float& deltaTime)
{
	if (m_CurrentPlayerState != nullptr)
	{
		m_CurrentPlayerState->Update(deltaTime);
	}

	// m_CurrentPlayerState->Update()の後に置く
	if (m_IsGround)
	{
		m_PlayerBulletCount = 0;
	}

	m_IsGround = false;
	m_IsHead = false;
}
void Player::CollisionControl()
{
	m_IsDamaged = false;
	m_IsAttackEnemy = false;
	if (m_Collision != nullptr)
	{
		// ブロックとの当たり判定
		if (m_Collision->CheckHitCollision(COLLISIONTAG::BLOCK))
		{
			HitBlock();
		}
		// エネミーとの当たり判定
		if (m_Collision->CheckHitCollision(COLLISIONTAG::ENEMY))
		{
			HitEnemy();
		}
	}
	// 無敵状態
	if (m_IsInv)
	{
		m_IsDamaged = false;
	}
}

void Player::FlashControl()
{
	if (m_FlashCurrentTime >= m_FLASH_TIME)
	{
		if (!m_Flash)
		{
			m_Flash = true;
		}
		else
		{
			m_Flash = false;
		}
		m_FlashCurrentTime = 0.0f;
	}

	if (m_Flash)
	{
		m_Texture = TEXTURE::NONE;
	}
}

// ブロックと当たった後
void Player::HitBlock()
{
	if (m_Collision != nullptr)
	{
		const HITDIRECTION& HitVertical = m_Collision->GetHitVertical();
		const HITDIRECTION& HitSide = m_Collision->GetHitSide();
		const XMFLOAT2& HitObjectPos = m_Collision->GetHitObjectPos();

		if (HitSide == HITDIRECTION::RIGHT || HitSide == HITDIRECTION::LEFT)
		{
			m_Position.x = HitObjectPos.x;
			m_Velocity.x = 0;
		}

		if (HitVertical != HITDIRECTION::DOWN && HitVertical != HITDIRECTION::UP)
		{
			return;
		}
	
		std::vector<Block*> HitBlockList = {};
		if (!m_Collision->GetHitGameObjects<Block>(HitBlockList)) return;
		bool IsFall = false;

		if (HitBlockList.size() >= m_HITOBJECT_COUNT_MIN)
		{
			// 壁に当たりながら落下できるように
			if (HitSide == HITDIRECTION::RIGHT || HitSide == HITDIRECTION::LEFT)
			{
				float RecordPosX = 0;
				for (Block* HitBlockObject : HitBlockList)
				{
					if (HitBlockObject == nullptr) continue;

					if (RecordPosX == 0)
					{
						RecordPosX = HitBlockObject->GetPos().x;
					}

					if (RecordPosX != HitBlockObject->GetPos().x)
					{
						IsFall = false;
						break;
					}
					IsFall = true;
				}
			}
		}

		if (IsFall) return;

		// 重力のリセット
		if (HitVertical == HITDIRECTION::DOWN)
		{
			InitGravityAcceleration();
			m_IsGround = true;
		}
		if (HitVertical == HITDIRECTION::UP)
		{
			m_IsHead = true;
			// 破壊可能なブロックに下から当たると壊れる
			if (!m_IsGround && GetVelocity().y < 0)
			{
				for (Block* HitBlockObject : HitBlockList)
				{
					if (HitBlockObject == nullptr) continue;
					if (HitBlockObject->GetBlockType() != BLOCK::BREAK) continue;

					HitBlockObject->Unit();
				}
			}
		}

		m_Position.y = HitObjectPos.y;
		m_Velocity.y = 0;
	}
}
// エネミーと当たった後
void Player::HitEnemy()
{
	if (m_Collision != nullptr)
	{
		if (!m_IsInv)
		{
			InitGravityAcceleration();
		}	
		m_IsGround = true;

		// 宙に浮かぶ敵と当たった時
		Jellyfish* JellyfishObject = m_Collision->GetHitGameObject<Jellyfish>();
		if (JellyfishObject != nullptr)
		{
			HitJellyfish(JellyfishObject);
			return;
		}

		// 地を這う敵と当たった時
		Snail* SnailObject = m_Collision->GetHitGameObject<Snail>();
		if (SnailObject != nullptr)
		{
			m_IsDamaged = true;
			TakeDamage(1);
			return;
		}
	}
}

void Player::HitJellyfish(Jellyfish* jellyfish)
{
	if (m_Collision != nullptr && jellyfish != nullptr)
	{
		const HITDIRECTION& HitVertical = m_Collision->GetHitVertical();
		const HITDIRECTION& HitSide = m_Collision->GetHitSide();

		if (HitSide == HITDIRECTION::RIGHT || HitSide == HITDIRECTION::LEFT || HitVertical == HITDIRECTION::UP)
		{
			TakeDamage(1);
		}
		// 上を優先
		if (HitVertical == HITDIRECTION::DOWN )
		{
			m_IsDamaged = false;
			m_IsAttackEnemy = true;
			jellyfish->TakeDamage(m_PLAYER_ATTACK);
		}
	}
}



