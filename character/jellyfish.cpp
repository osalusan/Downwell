#include "jellyfish.h"
#include "component/boxCollisionComponent.h"
#include "manager/sceneManager.h"
#include "player.h"
#include "map.h"
#include "object/block.h"
#include "scene/scene.h"

// �����ݒ�p�ϐ�
constexpr XMFLOAT2 m_SCALE_DEFAULT = { SCREEN_WIDTH * 0.09f,SCREEN_HEIGET * 0.16f };
constexpr int m_HEALTH_DEFAULT = 3;

// �ړ����x
constexpr XMFLOAT2 m_MOVE_SPEED_MAX = { (SCREEN_WIDTH * 0.039f),(SCREEN_HEIGET * 0.14f) };
constexpr XMFLOAT2 m_MOVE_SPEED = m_MOVE_SPEED_MAX;

// �����l
constexpr float m_REVERSE_VALUE = 1.0f;

Jellyfish::~Jellyfish()
{
	m_Player = nullptr;
}

void Jellyfish::Init()
{
	Character::Init();
	LoadTexture(TEXTURE::ENEMY_JELLYFISH, "asset\\texture\\T_Jellyfish.png");
	m_Scale = { MAPCHIP_WIDTH , MAPCHIP_HEIGHT };
	m_Health = m_HEALTH_DEFAULT;
	if (m_Collision != nullptr)
	{
		m_Collision->SetCollisionTag(COLLISIONTAG::ENEMY);
	}
}
// ----------------------------- private -----------------------------
void Jellyfish::MoveControl(const float& deltaTime)
{
	if (m_Player != nullptr)
	{
		const XMFLOAT2& MyPos = GetPos();
		const XMFLOAT2& PlayerPos = m_Player->GetPos();
		const XMFLOAT2& Vector = { PlayerPos.x - MyPos.x,PlayerPos.y - MyPos.y };
		
		// ����
		if (m_MoveReverseX)
		{
			m_Acceleration.x = -m_Acceleration.x * m_REVERSE_VALUE;
			m_MoveReverseX = false;
		}
		if (m_MoveReverseY)
		{
			m_Acceleration.y = -m_Acceleration.y * m_REVERSE_VALUE;
			m_MoveReverseY = false;
		}

		

		// �������Ɋ��
		if (Vector.x < 0)
		{
			m_Acceleration.x += -m_MOVE_SPEED.x * deltaTime;
		}
		else // �E�����Ɋ��
		{
			m_Acceleration.x += m_MOVE_SPEED.x * deltaTime;
		}
		
		// ������ɂ��
		if (Vector.y < 0)
		{
			m_Acceleration.y += -m_MOVE_SPEED.y * deltaTime;
		}
		else
		{
			m_Acceleration.y += m_MOVE_SPEED.y * deltaTime;
		}

		// �ō����x�ݒ�
		if (m_Acceleration.x >= m_MOVE_SPEED_MAX.x)
		{
			m_Acceleration.x = m_MOVE_SPEED_MAX.x;
		}
		else if (m_Acceleration.x <= -m_MOVE_SPEED_MAX.x)
		{
			m_Acceleration.x = -m_MOVE_SPEED_MAX.x;
		}
		if (m_Acceleration.y >= m_MOVE_SPEED_MAX.y)
		{
			m_Acceleration.y = m_MOVE_SPEED_MAX.y;
		}
		else if (m_Acceleration.y <= -m_MOVE_SPEED_MAX.y)
		{
			m_Acceleration.y = -m_MOVE_SPEED_MAX.y;
		}

		m_Velocity.x = m_Acceleration.x;
		m_Velocity.y = m_Acceleration.y;
	}
	else
	{
		// null�`�F�b�N
		Scene* Scene = SceneManager::GetScene();
		if (Scene == nullptr) return;

		Map* Map = Scene->GetMap();
		if (Map == nullptr) return;

		Player* PlayerObject = Map->GetPlayer();
		if (PlayerObject == nullptr) return;

		m_Player = PlayerObject;
	}
}

void Jellyfish::CollisionControl()
{
	if (m_Collision != nullptr)
	{
		// �u���b�N�Ƃ̓����蔻��
		if (m_Collision->CheckHitCollision(COLLISIONTAG::BLOCK))
		{
			HitBlock();
		}
		if (m_Collision->CheckHitCollision(COLLISIONTAG::ENEMY))
		{
			HitEnemy();
		}
	}
}

void Jellyfish::HitBlock()
{
	// �u���b�N�Ƃ̓����蔻��
	if (m_Collision != nullptr)
	{
		const HITDIRECTION& HitVertical = m_Collision->GetHitVertical();
		const HITDIRECTION& HitSide = m_Collision->GetHitSide();
		const XMFLOAT2& HitObjectPos = m_Collision->GetHitObjectPos();

		std::vector<Block*> BlockList = {};
		m_Collision->GetHitGameObjects<Block>(BlockList);
		bool IsSide = false;
		bool IsVertical = false;

		if (BlockList.size() >= m_HITOBJECT_COUNT_MIN)
		{
			// �ǂɓ�����Ȃ��痎���ł���悤��
			if (HitSide == HITDIRECTION::RIGHT || HitSide == HITDIRECTION::LEFT)
			{
				float RecordPosX = 0;
				for (Block* BlockObject : BlockList)
				{
					if (RecordPosX == 0)
					{
						RecordPosX = BlockObject->GetPos().x;
					}

					if (RecordPosX != BlockObject->GetPos().x)
					{
						IsVertical = false;
						break;
					}
					IsVertical = true;
				}
			}

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
						IsSide = false;
						break;
					}
					IsSide = true;
				}
			}
		}

		// ���ɕ���ł���u���b�N�̉����肾������X���[
		if (!IsSide)
		{
			if (HitSide == HITDIRECTION::RIGHT || HitSide == HITDIRECTION::LEFT)
			{
				m_Position.x = HitObjectPos.x;
			}
		}

		// �c�ɕ���ł���u���b�N�̏c���肾������X���[
		if (!IsVertical)
		{
			if (HitVertical == HITDIRECTION::DOWN || HitVertical == HITDIRECTION::UP)
			{
				m_Position.y = HitObjectPos.y;
				m_MoveReverseY = true;
			}
		}
	}
}

void Jellyfish::HitEnemy()
{
	if (m_Collision != nullptr)
	{
		const HITDIRECTION& HitVertical = m_Collision->GetHitVertical();
		const HITDIRECTION& HitSide = m_Collision->GetHitSide();
		const XMFLOAT2& HitObjectPos = m_Collision->GetHitObjectPos();

		if (HitSide == HITDIRECTION::RIGHT || HitSide == HITDIRECTION::LEFT)
		{
			m_Position.x = HitObjectPos.x;
			m_MoveReverseX = true;
		}

		if (HitVertical == HITDIRECTION::DOWN || HitVertical == HITDIRECTION::UP)
		{
			m_Position.y = HitObjectPos.y;
			m_MoveReverseY = true;
		}
	}
}
