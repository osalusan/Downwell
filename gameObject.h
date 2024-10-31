#pragma once
#include "main.h"
#include <string>
#include "manager/textureManager.h"

class GameObject {
protected:
	TEXTURE m_Texture = TEXTURE::NONE;	// 読み込んだテクスチャ
	bool m_Enable = true;				// 利用可能か
	XMFLOAT2 m_Position = {};			// 座標
	XMFLOAT2 m_Scale = {};				// 大きさ
	XMFLOAT2 m_Rotation = {};			// 回転

public:
	GameObject() = default; // コンストラクタ
	virtual ~GameObject() {};
	virtual void Init() = 0;
	virtual void Unit() = 0;
	virtual void Update(const float& deltaTime) = 0;
	virtual void Draw(const XMFLOAT2& cameraPos);
	void LoadTexture(const TEXTURE& texture, const std::string& fileName);

	const XMFLOAT2& GetScale()const
	{ 
		return m_Scale; 
	}
	const XMFLOAT2& GetPos()const
	{ 
		return m_Position; 
	}
	const bool& GetEnable()const 
	{ 
		return m_Enable; 
	}
	void Disable()
	{
		m_Enable = false;
	}
};