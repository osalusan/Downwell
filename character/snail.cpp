#include "snail.h"
#include "component/boxCollisionComponent.h"
#include "map.h"
#include "object/block.h"

// �����ݒ�p�ϐ�
constexpr XMFLOAT2 m_SCALE_DEFAULT = { MAPCHIP_WIDTH - 10.0f , MAPCHIP_HEIGHT };
constexpr int m_HEALTH_DEFAULT = 1;

// ���x
constexpr float m_MOVE_SPEED = (SCREEN_WIDTH * 4.5f);			// �ړ����x
constexpr float m_GRAVITY_DEFAULT = (SCREEN_HEIGET * 0.92f);	// �z�u���Ƀu���b�N���������ɗL����

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
		// �ЂƂO�̃u���b�N�̓����蔻��
		CheckPreviousBlock();
		// �u���b�N�Ƃ̓����蔻��
		if (m_Collision->CheckHitCollision(COLLISIONTAG::BLOCK))
		{
			HitBlock();
		}
	}
}

void Snail::HitBlock()
{
	// �u���b�N�Ƃ̓����蔻��
	if (m_Collision != nullptr)
	{
		const HITDIRECTION& HitVertical = m_Collision->GetHitVertical();
		const HITDIRECTION& HitSide = m_Collision->GetHitSide();
		const XMFLOAT2& HitObjectPos = m_Collision->GetHitObjectPos();


		// �d�͂̃��Z�b�g
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


		// �n�ʂɂ���u���b�N�̉����肾������X���[
		if (IsGround) 
		{
			// �Ō�ɌĂяo��
			if (HitVertical == HITDIRECTION::DOWN)
			{
				if (m_MoveDirection == MOVEDIRECTION::NONE)
				{
					m_MoveDirection = MOVEDIRECTION::RIGHT;
				}
			}
			return;
		}

		// ���̒��˕Ԃ�
		if (HitSide == HITDIRECTION::RIGHT)
		{
			m_MoveDirection = MOVEDIRECTION::LEFT;
		}
		else if (HitSide == HITDIRECTION::LEFT)
		{
			m_MoveDirection = MOVEDIRECTION::RIGHT;
		}

		// �Ō�ɌĂяo��
		if (HitVertical == HITDIRECTION::DOWN)
		{
			if (m_MoveDirection == MOVEDIRECTION::NONE)
			{
				m_MoveDirection = MOVEDIRECTION::RIGHT;
			}
		}
	}
}

// �ЂƂO�̃u���b�N���m�F
void Snail::CheckPreviousBlock()
{
	if (m_Collision != nullptr)
	{
		// ���݂̍��W��ۑ�
		m_CurrentPos = m_Position;

		// �ړ������ɑ傫�����A����炵�����W��ݒ�
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

		// ���̃u���b�N���Ȃ�������
		if (!m_Collision->CheckHitCollision(COLLISIONTAG::BLOCK))
		{
			// �㉺���E�̒��˕Ԃ�
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

		// ���̈ʒu�ɖ߂�
		m_Position = m_CurrentPos;
	}
}
