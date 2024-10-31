#pragma once
#include "object/block.h"
#include <vector>
#include <list>

// 前方宣言
class Camera;


class BlockManager final
{
private:
	std::list<Block*> m_Blocks[static_cast<int>(BLOCK::MAX) - 1] = { {} };			// 生成したブロック

public:
	~BlockManager();
	void Unit();
	void Update(const float& deltaTime);
	void Draw(const XMFLOAT2& pos);
	void CreateBlock(const BLOCK& type, const XMFLOAT2& pos);	// ブロックの生成

	// 有効である全てのBlockを取得
	bool GetEnableBlockObjects(std::vector<Block*>& vector);
};