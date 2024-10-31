#include "snail.h"
#include "component/boxCollisionComponent.h"
#include "map.h"
#include "object/block.h"

// 初期設定用変数
constexpr XMFLOAT2 m_SCALE_DEFAULT = { MAPCHIP_WIDTH - 10.0f , MAPCHIP_HEIGHT };
constexpr int m_HEALTH_DEFAULT = 1;

// 速度
constexpr float m_MOVE_SPEED = (SCREEN_WIDTH * 4.5f);			// 移動速度
constexpr float m_GRAVITY_DEFAULT = (SCREEN_HEIGET * 0.92f);	// 配置時にブロックが無い時に有効に

void Snail::Init()
{
	Character::Init();
	LoadTexture(TEXTURE::ENEMY_SNAIL, "asset\\texture\\T_Snail.png");
	m_Scale = { m_SCALE_DEFAULT.x , m_SCALE_DEFAULT.y };
	m_Health = m_HEALTH_DEFAULT;

	if (m_Collision != nullptr)
	{
		m_Collision->SetCollisionTag(COLLISIONTAG::ENEMY);
	}
	m_GravityValue = m_GRAVITY_DEFAULT;
	m_EnableGravity = true;
}


void Snail::MoveControl(const float& deltaTime)
{
	switch (m_MoveDirection)
	{
	case MOVEDIRECTION::RIGHT:
		m_Velocity.x = m_MOVE_SPEED * deltaTime;
		break;

	case MOVEDIRECTION::LEFT:
		m_Velocity.x = -m_MOVE_SPEED * deltaTime;
		break;

	default:
		break;
	}
}

void Snail::CollisionControl()
{
	if (m_Collision != nullptr)
	{
		// ひとつ前のブロックの当たり判定
		CheckPreviousBlock();
		// ブロックとの当たり判定
		if (m_Collision->CheckHitCollision(COLLISIONTAG::BLOCK))
		{
			HitBlock();
		}
	}
}

void Snail::HitBlock()
{
	// ブロックとの当たり判定
	if (m_Collision != nullptr)
	{
		const HITDIRECTION& HitVertical = m_Collision->GetHitVertical();
		const HITDIRECTION& HitSide = m_Collision->GetHitSide();
		const XMFLOAT2& HitObjectPos = m_Collision->GetHitObjectPos();


		// 重力のリセット
		if (HitVertical == HITDIRECTION::DOWN)
		{
			InitGravityAcceleration();
			m_Position.y = HitObjectPos.y;
			m_Velocity.y = 0;
		}

		std::vector<Block*> BlockList = {};
		m_Collision->GetHitGameObjects<Block>(BlockList);
		bool IsGround = false;
		
		if (BlockList.size() >= m_HITOBJECT_COUNT_MIN)
		{
			if (HitSide == HITDIRECTION::RIGHT || HitSide == HITDIRECTION::LEFT)
			{
				float RecordPosY = 0;
				for (Block* BlockObject : BlockList)
				{
					if (RecordPosY == 0)
					{
						RecordPosY = BlockObject->GetPos().y;
					}

					if (RecordPosY != BlockObject->GetPos().y)
					{
						IsGround = false;
						break;
					}
					IsGround = true;
				}
			}
		}


		// 地面にあるブロックの横判定だったらスルー
		if (IsGround) 
		{
			// 最後に呼び出し
			if (HitVertical == HITDIRECTION::DOWN)
			{
				if (m_MoveDirection == MOVEDIRECTION::NONE)
				{
					m_MoveDirection = MOVEDIRECTION::RIGHT;
				}
			}
			return;
		}

		// 横の跳ね返り
		if (HitSide == HITDIRECTION::RIGHT)
		{
			m_MoveDirection = MOVEDIRECTION::LEFT;
		}
		else if (HitSide == HITDIRECTION::LEFT)
		{
			m_MoveDirection = MOVEDIRECTION::RIGHT;
		}

		// 最後に呼び出し
		if (HitVertical == HITDIRECTION::DOWN)
		{
			if (m_MoveDirection == MOVEDIRECTION::NONE)
			{
				m_MoveDirection = MOVEDIRECTION::RIGHT;
			}
		}
	}
}

// ひとつ前のブロックを確認
void Snail::CheckPreviousBlock()
{
	if (m_Collision != nullptr)
	{
		// 現在の座標を保存
		m_CurrentPos = m_Position;

		// 移動方向に大きさ分、一つずらした座標を設定
		switch (m_MoveDirection)
		{
		case MOVEDIRECTION::RIGHT:
			m_Position.x += m_Scale.x;
			break;

		case MOVEDIRECTION::LEFT:
			m_Position.x -= m_Scale.x;
			break;

		default:
			break;
		}

		// 次のブロックがなかったら
		if (!m_Collision->CheckHitCollision(COLLISIONTAG::BLOCK))
		{
			// 上下左右の跳ね返り
			switch (m_MoveDirection)
			{
			case MOVEDIRECTION::RIGHT:
				m_MoveDirection = MOVEDIRECTION::LEFT;
				break;

			case MOVEDIRECTION::LEFT:
				m_MoveDirection = MOVEDIRECTION::RIGHT;
				break;

			default:
				break;
			}
		}

		// 元の位置に戻す
		m_Position = m_CurrentPos;
	}
}
