#pragma once
#include "component.h"
#include <vector>
#include "main.h"

enum class HITDIRECTION
{
	NONE = 0,
	UP,
	DOWN,
	RIGHT,
	LEFT
};
enum class COLLISIONTAG
{
	NONE = 0,
	BLOCK,
	ENEMY,
	BULLET
};

// �O���錾
class Camera;
class Scene;
class Map;

class CollisionComponent :public Component
{
protected:
	bool m_Enable = true;								 // �����蔻��̗L������
	XMFLOAT2 m_Size = {};
	HITDIRECTION m_HitVertical = HITDIRECTION::NONE;     // �㉺�̂ǂ��炩�ɓ������Ă���
	HITDIRECTION m_HitSide = HITDIRECTION::NONE;         // ���E�̂ǂ��炩�ɓ������Ă���
	XMFLOAT2 m_Pos = {};								 // ����������Ɉړ�������l

	COLLISIONTAG m_CollisionTag = COLLISIONTAG::NONE;	 // �����蔻��̑���

	std::vector<GameObject*> m_HitGameObjects = {};		 // ���������I�u�W�F�N�g�̕ۑ��p
	Camera* m_CameraCache = nullptr;						 // �J�����̃|�C���^�ۑ��p
	Scene* m_Scene = nullptr;							 // Scene�̃|�C���^�ۑ��p
	Map* m_Map = nullptr;								 // Map�̃|�C���^�ۑ��p

	bool HitBoxCollision(GameObject* obj);
	void CheckHitDirection(GameObject* obj);
	void SetHitObject(GameObject* obj);					 // �ǂ̃I�u�W�F�N�g������������
public:
	using Component::Component;
	~CollisionComponent();
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update()override;
	virtual void Draw()override;
	void SetCollisionTag(const COLLISIONTAG tag);
	bool CheckHitCollision(const COLLISIONTAG tag);
	const HITDIRECTION& GetHitVertical()const 
	{ 
		return m_HitVertical; 
	}
	const HITDIRECTION& GetHitSide()const 
	{ 
		return m_HitSide; 
	}
	const XMFLOAT2& GetHitObjectPos()const 
	{ 
		return m_Pos; 
	}

	// �ŏ��̈�݂̂��擾
	template <typename T>
	T* GetHitGameObject()
	{
		for (GameObject* Object : m_HitGameObjects)
		{
			if (Object == nullptr) continue;

			if (T* HitObject = dynamic_cast<T*>(Object))
			{
				return HitObject;
			}
		}

		return nullptr;
	}

	// ���������I�u�W�F�N�g�S�Ă��擾
	template <typename T>
	bool GetHitGameObjects(std::vector<T*>& objectList)
	{
		for (GameObject* Object : m_HitGameObjects)
		{
			if (Object == nullptr) continue;

			if (T* HitObject = dynamic_cast<T*>(Object))
			{
				objectList.emplace_back(HitObject);
			}
		}
		return !objectList.empty();
	}
};