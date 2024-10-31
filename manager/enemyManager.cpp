#include "manager/enemyManager.h"
#include "character/jellyfish.h"
#include "character/snail.h"
#include "manager/sceneManager.h"
#include "character/enemy.h"
#include "map.h"

EnemyManager::~EnemyManager()
{
	// 現在保持している全てのEnemyの削除
	for (int i = 0; i < static_cast<int>(ENEMY::MAX) - 1; i++)
	{
		for (Enemy* EnemyObject : m_Enemys[i])
		{
			delete EnemyObject;
			EnemyObject = nullptr;
		}
	}
}

void EnemyManager::Unit()
{
	// 現在保持している全てのEnemyの終了処理
	for (int i = 0; i < static_cast<int>(ENEMY::MAX) - 1; i++)
	{
		for (Enemy* EnemyObject : m_Enemys[i])
		{
			// nullチェック
			if (EnemyObject == nullptr) continue;

			EnemyObject->Unit();
		}
	}
}

void EnemyManager::Update(const float& deltaTime)
{
	// 現在保持している全てのEnemyの更新
	for (int i = 0; i < static_cast<int>(ENEMY::MAX) - 1; i++)
	{
		for (Enemy* EnemyObject : m_Enemys[i])
		{
			// 使用不可
			if (EnemyObject == nullptr) continue;
			if (!EnemyObject->GetEnable()) continue;

			EnemyObject->Update(deltaTime);
		}
	}
}

void EnemyManager::Draw(const XMFLOAT2& pos)
{
	// 現在保持している全てのEnemyの描画
	for (int i = 0; i < static_cast<int>(ENEMY::MAX) - 1; i++)
	{
		for (Enemy* EnemyObject : m_Enemys[i])
		{
			// 使用不可
			if (EnemyObject == nullptr) continue;
			if (!EnemyObject->GetEnable()) continue;

			EnemyObject->Draw(pos);
		}
	}
}

void EnemyManager::CreateEnemy(const ENEMY& type,const XMFLOAT2& pos)
{
	// 利用可能な敵がいたらその値を返す
	for (Enemy* EnemyObject : m_Enemys[static_cast<int>(type) - 1])
	{
		// 利用不可
		if (EnemyObject == nullptr) continue;
		if (EnemyObject->GetEnable()) continue;

		// 利用可能
		EnemyObject->SetEnemyPos(pos);

		return;
	}
	// 利用可能な敵がいなかったら新しく生成
	Enemy* EnemyNewObject = nullptr;
	switch (type)
	{
	case ENEMY::JELLYFISH:
		EnemyNewObject = new Jellyfish;
		break;

	case ENEMY::SNAIL:
		EnemyNewObject = new Snail;
		break;

	default:
		break;
	}

	if (EnemyNewObject != nullptr)
	{
		EnemyNewObject->SetEnemyPos(pos);
		m_Enemys[static_cast<int>(type) - 1].emplace_back(EnemyNewObject);
	}
}

bool EnemyManager::GetEnableEnemyObjects(std::vector<Enemy*>& vector)
{
	for (int i = 0; i < static_cast<int>(ENEMY::MAX) - 1; i++)
	{
		for (Enemy* EnemyObject : m_Enemys[i])
		{
			// 無効だったら次へ
			if (EnemyObject == nullptr) continue;

			if (!EnemyObject->GetEnable()) continue;

			vector.emplace_back(EnemyObject);
		}
	}
	return !vector.empty();
}
