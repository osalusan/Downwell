#pragma once
#include "object/block.h"
#include <vector>
#include <list>

// �O���錾
class Camera;


class BlockManager final
{
private:
	std::list<Block*> m_Blocks[static_cast<int>(BLOCK::MAX) - 1] = { {} };			// ���������u���b�N

public:
	~BlockManager();
	void Unit();
	void Update(const float& deltaTime);
	void Draw(const XMFLOAT2& pos);
	void CreateBlock(const BLOCK& type, const XMFLOAT2& pos);	// �u���b�N�̐���

	// �L���ł���S�Ă�Block���擾
	bool GetEnableBlockObjects(std::vector<Block*>& vector);
};