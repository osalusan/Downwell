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

// 前方宣言
class Camera;
class Scene;
class Map;

class CollisionComponent :public Component
{
protected:
	bool m_Enable = true;								 // 当たり判定の有効無効
	XMFLOAT2 m_Size = {};
	HITDIRECTION m_HitVertical = HITDIRECTION::NONE;     // 上下のどちらかに当たっている
	HITDIRECTION m_HitSide = HITDIRECTION::NONE;         // 左右のどちらかに当たっている
	XMFLOAT2 m_Pos = {};								 // 当たった後に移動させる値

	COLLISIONTAG m_CollisionTag = COLLISIONTAG::NONE;	 // 当たり判定の属性

	std::vector<GameObject*> m_HitGameObjects = {};		 // 当たったオブジェクトの保存用
	Camera* m_CameraCache = nullptr;						 // カメラのポインタ保存用
	Scene* m_Scene = nullptr;							 // Sceneのポインタ保存用
	Map* m_Map = nullptr;								 // Mapのポインタ保存用

	bool HitBoxCollision(GameObject* obj);
	void CheckHitDirection(GameObject* obj);
	void SetHitObject(GameObject* obj);					 // どのオブジェクトが当たったか
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

	// 最初の一つのみを取得
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

	// 当たったオブジェクト全てを取得
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