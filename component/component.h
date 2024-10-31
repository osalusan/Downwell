#pragma once

// ‘O•ûéŒ¾
class GameObject;

class Component
{
protected:
	GameObject* m_GameObject = nullptr;
public:
	Component() = delete;
	Component(GameObject* gameObj) 
	{ 
		m_GameObject = gameObj; 
	}
	virtual ~Component()
	{
		m_GameObject = nullptr;
	}
	virtual void Init() = 0;
	virtual void Unit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};