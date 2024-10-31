#pragma once
#include "main.h"
#include <string>
#include "manager/textureManager.h"

class GameObject {
protected:
	TEXTURE m_Texture = TEXTURE::NONE;	// �ǂݍ��񂾃e�N�X�`��
	bool m_Enable = true;				// ���p�\��
	XMFLOAT2 m_Position = {};			// ���W
	XMFLOAT2 m_Scale = {};				// �傫��
	XMFLOAT2 m_Rotation = {};			// ��]

public:
	GameObject() = default; // �R���X�g���N�^
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