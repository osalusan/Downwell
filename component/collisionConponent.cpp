#include "component/collisionConponent.h"
#include "manager/sceneManager.h"
#include "object/block.h"
#include "manager/textureManager.h"
#include "manager/enemyManager.h"
#include "manager/blockManager.h"
#include "camera.h"
#include <vector>
#include "character/enemy.h"
#include "map.h"
#include "gameObject.h"
#include "scene/scene.h"
#include "component/boxCollisionComponent.h"

CollisionComponent::~CollisionComponent()
{
	m_GameObject = nullptr;
	m_CameraCache = nullptr;	
	m_Map = nullptr;
}

void CollisionComponent::Init()
{
	if (m_Size.x == 0 && m_Size.y == 0)
	{
		if (m_GameObject != nullptr)
		{
			m_Size = m_GameObject->GetScale();
		}
	}
	m_Enable = true;

	// Scene�̊i�[
	if (m_Scene == nullptr)
	{
		m_Scene = SceneManager::GetScene();
		if (m_Scene == nullptr) return;
	}

	if (m_Map == nullptr)
	{
		m_Map = m_Scene->GetMap();
		if (m_Map == nullptr) return;
	}

}

void CollisionComponent::Unit()
{
	m_Enable = false;
	m_CollisionTag = COLLISIONTAG::NONE;
}

// �����蔻��̕������擾�������I�u�W�F�N�g�̂�Update������
void CollisionComponent::Update()
{
	if (m_Size.x == 0 && m_Size.y == 0)
	{
		if (m_GameObject != nullptr)
		{
			m_Size = m_GameObject->GetScale();
		}
	}

	// �O�t���[���̋L�^���폜
	m_HitVertical = HITDIRECTION::NONE;
	m_HitSide = HITDIRECTION::NONE;
	m_Pos = {};
	m_HitGameObjects = {};
}

void CollisionComponent::Draw()
{
#if _DEBUG 
	// �����\���ł̓����蔻��\�� / DEBUG���̂�
	if (SHOW_COLLISION)
	{
		// �����̎�
		if (m_Enable == false) return;

		// �J�����̃|�C���^���i�[
		if (m_CameraCache == nullptr)
		{
			if (m_Map == nullptr) return;

			m_CameraCache = m_Map->GetCamera();
			if (m_CameraCache == nullptr) return;
		}

		// null�`�F�b�N
		if (m_GameObject == nullptr || m_CameraCache == nullptr)
		{
			return;
		}

		const XMFLOAT2& ObjectPos = m_GameObject->GetPos();
		const XMFLOAT2& CameraPos = m_CameraCache->GetPos();
		const XMFLOAT2& HalfSize = { m_Size.x / 2 ,m_Size.y / 2 };

		const int& Left = static_cast<int>(ObjectPos.x - HalfSize.x);
		const int& Right = static_cast<int>(ObjectPos.x + HalfSize.x);
		const int& Top = static_cast<int>(ObjectPos.y - HalfSize.y + CameraPos.y);
		const int& Under = static_cast<int>(ObjectPos.y + HalfSize.y + CameraPos.y);

		// �l�p
		DrawBox(Left, Top,Right, Under, GetColor(255, 0, 0), false);
		// �΂�
		DrawLine(Left, Top,Right, Under, GetColor(255, 0, 0));

		std::string DrawDirectionSide = {};
		std::string DrawDirectionVirtical = {};
		const HITDIRECTION& Vertical = m_HitVertical;
		const HITDIRECTION& Side = m_HitSide;

		if (Vertical == HITDIRECTION::UP)
		{ 
			DrawDirectionVirtical = "��Ƀq�b�g"; 
		}
		if (Vertical == HITDIRECTION::DOWN)
		{ 
			DrawDirectionVirtical = "���Ƀq�b�g"; 
		}
		if (Side == HITDIRECTION::RIGHT)
		{
			DrawDirectionSide = "�E�Ƀq�b�g"; 
		}
		if (Side == HITDIRECTION::LEFT)
		{ 
			DrawDirectionSide = "���Ƀq�b�g"; 
		}
		DrawString(Right, Under, DrawDirectionSide.c_str(), GetColor(0, 0, 255));
		DrawString(Right, Top, DrawDirectionVirtical.c_str(), GetColor(0, 0, 255));
	}
#endif
}

void CollisionComponent::SetCollisionTag(const COLLISIONTAG tag)
{
	m_CollisionTag = tag;
}

// Tag�̃I�u�W�F�N�g�Ɠ������Ă��邩
bool CollisionComponent::CheckHitCollision(const COLLISIONTAG tag)
{
	m_HitVertical = HITDIRECTION::NONE;
	m_HitSide = HITDIRECTION::NONE;
	m_Pos = {};
	m_HitGameObjects = {};

	if (m_Scene == nullptr) return false;
	if (m_Map == nullptr) return false;

	// return�Ŏg�p
	bool IsHit = false;

	switch (tag)
	{
	case COLLISIONTAG::BLOCK:
	{
		std::vector<Block*> BlockList = {};
		BlockManager* BlockManager = m_Map->GetBlockManager();

		if (BlockManager != nullptr)
		{
			BlockManager->GetEnableBlockObjects(BlockList);
		}
	
		for (Block* BlockObject : BlockList)
		{
			// null�`�F�b�N
			if (BlockObject == nullptr) continue;

			// �ŏ��̈�݂̂�return���Ȃ��悤��
			if (HitBoxCollision(BlockObject))
			{
				CheckHitDirection(BlockObject);
				SetHitObject(BlockObject);
				IsHit = true;
			}
		}
		return IsHit;
		break;
	}
	case COLLISIONTAG::ENEMY:
	{
		std::vector<Enemy*> EnemyList = {};
		EnemyManager* EnemyManager = m_Map->GetEnemymanager();

		if (EnemyManager != nullptr)
		{
			EnemyManager->GetEnableEnemyObjects(EnemyList);
		}

		for (Enemy* EnemyObject : EnemyList)
		{
			// �����������玟��
			if (EnemyObject == nullptr) continue;
			if (EnemyObject == m_GameObject) continue;

			// �l�p�̓����蔻��
			if (BoxCollisionComponent* Box = dynamic_cast<BoxCollisionComponent*>(EnemyObject->GetCollisionComponent()))
			{
				// �ŏ��̈�݂̂�return���Ȃ��悤��
				if (HitBoxCollision(EnemyObject))
				{
					CheckHitDirection(EnemyObject);
					SetHitObject(EnemyObject);
					IsHit = true;
				}
			}
		}
		
		return IsHit;
		break;
	}
	default:
		break;
	}

	return false;
}


// -------------------------------private-------------------------------
bool CollisionComponent::HitBoxCollision(GameObject* obj)
{
	// null�`�F�b�N
	if (m_GameObject != nullptr && obj != nullptr)
	{
		const XMFLOAT2& MyObjectPos = m_GameObject->GetPos();
		const XMFLOAT2& MyObjectScale = m_GameObject->GetScale();
		const XMFLOAT2& ObjectPos = obj->GetPos();
		const XMFLOAT2& ObjectScale = obj->GetScale();

		const XMFLOAT2& Scale = { (MyObjectScale.x + ObjectScale.x) / 2,(MyObjectScale.y + ObjectScale.y) / 2 };

		// �����蔻��
		if (MyObjectPos.x - ObjectPos.x < Scale.x &&
			MyObjectPos.x - ObjectPos.x > -Scale.x)
		{
			if (MyObjectPos.y - ObjectPos.y < Scale.y &&
				MyObjectPos.y - ObjectPos.y > -Scale.y)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

void CollisionComponent::CheckHitDirection(GameObject* obj)
{
	// null�`�F�b�N
	if (m_GameObject != nullptr && obj != nullptr)
	{
		const XMFLOAT2& MyObjectPos = m_GameObject->GetPos();
		const XMFLOAT2& MyObjectScale = m_GameObject->GetScale();
		const XMFLOAT2& ObjectPos = obj->GetPos();
		const XMFLOAT2& ObjectScale = obj->GetScale();
		const XMFLOAT2& Vector = { ObjectPos.x - MyObjectPos.x,ObjectPos.y - MyObjectPos.y};
		const XMFLOAT2& Scale = { (MyObjectScale.x + ObjectScale.x) / 2,(MyObjectScale.y + ObjectScale.y) / 2 };

		if (abs(Vector.x) < abs(Vector.y))
		{
			if (Vector.y < 0)
			{
				m_HitVertical = HITDIRECTION::UP; 
				m_Pos.y = ObjectPos.y + Scale.y;
			}
			else
			{
				m_HitVertical = HITDIRECTION::DOWN; 
				m_Pos.y = ObjectPos.y - Scale.y;
			}
		}
		else
		{
			if (Vector.x < 0)
			{
				m_HitSide = HITDIRECTION::LEFT; 
				m_Pos.x = ObjectPos.x + Scale.x;
			}
			else
			{
				m_HitSide = HITDIRECTION::RIGHT; 
				m_Pos.x = ObjectPos.x - Scale.x;
			}
		}
	}
}

void CollisionComponent::SetHitObject(GameObject* obj)
{
	if (obj != nullptr)
	{
		m_HitGameObjects.emplace_back(obj);
	}
}

