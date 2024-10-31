#include "object/block.h"
#include "map.h"
#include "manager/sceneManager.h"
#include "camera.h"
#include "component/boxCollisionComponent.h"

Block::Block(const BLOCK& blockType, const XMFLOAT2& pos)
{
	m_BlockType = blockType;

	m_Position = pos;

	m_Scale = { MAPCHIP_WIDTH , MAPCHIP_HEIGHT };

	// �e�N�X�`���̓ǂݍ���
	switch (m_BlockType)
	{
	case BLOCK::UNBREAK:
		LoadTexture(TEXTURE::BLOCK_UNBREAK, "asset\\texture\\T_UnBreakBlock.png");
		break;
	case BLOCK::BREAK:
		LoadTexture(TEXTURE::BLOCK_BREAK, "asset\\texture\\T_BreakBlock.png");
		break;
	default:
		break;
	}
}

Block::~Block()
{
	delete m_BoxCollision; 
	m_BoxCollision = nullptr;
}

void Block::Init()
{
	// �����蔻��̍쐬
	if (m_BoxCollision == nullptr)
	{
		m_BoxCollision = new BoxCollisionComponent(this);
	}

	if (m_BoxCollision != nullptr)
	{
		m_BoxCollision->Init();
		m_BoxCollision->SetCollisionTag(COLLISIONTAG::BLOCK);
	}

	m_Enable = true;
}

void Block::Unit()
{
	m_Enable = false;
	if (m_BoxCollision != nullptr)
	{
		m_BoxCollision->Unit();
	}
}

void Block::Update(const float& deltaTime)
{
	// GameObject�̏������z�֐��̈׋����
}

void Block::Draw(const XMFLOAT2& cameraPos)
{

	GameObject::Draw(cameraPos);
	if (m_BoxCollision != nullptr)
	{
		m_BoxCollision->Draw();
	}
}

void Block::SetBlockPos(const XMFLOAT2& pos)
{
	m_Position = pos;
	Init();
}
