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
			// �����������玟��
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
			// �����������玟��
			if (BlockObject == nullptr) continue;
			if (!BlockObject->GetEnable()) continue;

			BlockObject->Draw(pos);
		}
	}
}

void BlockManager::CreateBlock(const BLOCK& type, const XMFLOAT2& pos)
{
	// ���p�\�ȓG�������炻�̒l��Ԃ�
	for (Block* BlockObject : m_Blocks[static_cast<int>(type) - 1])
	{
		// ���p�s��
		if (BlockObject == nullptr) continue;
		if (BlockObject->GetEnable()) continue;

		// ���p�\
		BlockObject->SetBlockPos(pos);

		return;
	}
	// ���p�\�ȓG�����Ȃ�������V��������
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
			// �����������玟��
			if (BlockObject == nullptr) continue;

			if (!BlockObject->GetEnable()) continue;

			vector.emplace_back(BlockObject);
		}
	}
	return !vector.empty();
}

