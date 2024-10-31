#pragma once
#include "gameObject.h"

class BoxCollisionComponent;

enum class BLOCK
{
	NONE = 0,
	UNBREAK,
	BREAK,
	MAX
};
class Block final :public GameObject
{
private:
	BLOCK m_BlockType = BLOCK::NONE;
	BoxCollisionComponent* m_BoxCollision = nullptr;
public:
	Block() = delete;
	Block(const BLOCK& blockType,const XMFLOAT2& pos);
	~Block();
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update(const float& deltaTime)override;
	virtual void Draw(const XMFLOAT2& cameraPos)override;

	void SetBlockPos(const XMFLOAT2& pos);

	const BLOCK& GetBlockType()
	{
		return m_BlockType;
	}
};