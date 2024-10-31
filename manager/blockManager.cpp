#include "blockManager.h"

BlockManager::~BlockManager()
{
	for (int i = 0; i < static_cast<int>(BLOCK::MAX) - 1; i++)
	{
		for (Block* BlockObject : m_Blocks[i])
		{
			delete BlockObject;
			BlockObject = nullptr;
		}
		m_Blocks[i].clear();
	}
}

void BlockManager::Unit()
{
	for (int i = 0; i < static_cast<int>(BLOCK::MAX) - 1; i++)
	{
		for (Block* BlockObject : m_Blocks[i])
		{
			if (BlockObject == nullptr) continue;

			BlockObject->Unit();
		}
	}
}

void BlockManager::Update(const float& deltaTime)
{
	for (int i = 0; i < static_cast<int>(BLOCK::MAX) - 1; i++)
	{
		for (Block* BlockObject : m_Blocks[i])
		{
			// 無効だったら次へ
			if (BlockObject == nullptr) continue;
			if (!BlockObject->GetEnable()) continue;

			BlockObject->Update(deltaTime);
		}
	}
}

void BlockManager::Draw(const XMFLOAT2& pos)
{
	for (int i = 0; i < static_cast<int>(BLOCK::MAX) - 1; i++)
	{
		for (Block* BlockObject : m_Blocks[i])
		{
			// 無効だったら次へ
			if (BlockObject == nullptr) continue;
			if (!BlockObject->GetEnable()) continue;

			BlockObject->Draw(pos);
		}
	}
}

void BlockManager::CreateBlock(const BLOCK& type, const XMFLOAT2& pos)
{
	// 利用可能な敵がいたらその値を返す
	for (Block* BlockObject : m_Blocks[static_cast<int>(type) - 1])
	{
		// 利用不可
		if (BlockObject == nullptr) continue;
		if (BlockObject->GetEnable()) continue;

		// 利用可能
		BlockObject->SetBlockPos(pos);

		return;
	}
	// 利用可能な敵がいなかったら新しく生成
	Block* BlockNewObject = new Block(type,pos);

	if (BlockNewObject != nullptr)
	{
		BlockNewObject->SetBlockPos(pos);
		m_Blocks[static_cast<int>(type) - 1].emplace_back(BlockNewObject);
	}
}

bool BlockManager::GetEnableBlockObjects(std::vector<Block*>& vector)
{
	for (int i = 0; i < static_cast<int>(BLOCK::MAX) - 1; i++)
	{
		for (Block* BlockObject : m_Blocks[i])
		{
			// 無効だったら次へ
			if (BlockObject == nullptr) continue;

			if (!BlockObject->GetEnable()) continue;

			vector.emplace_back(BlockObject);
		}
	}
	return !vector.empty();
}

