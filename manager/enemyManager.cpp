#include "manager/enemyManager.h"
#include "character/jellyfish.h"
#include "character/snail.h"
#include "manager/sceneManager.h"
#include "character/enemy.h"
#include "map.h"

EnemyManager::~EnemyManager()
{
	// ���ݕێ����Ă���S�Ă�Enemy�̍폜
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
	// ���ݕێ����Ă���S�Ă�Enemy�̏I������
	for (int i = 0; i < static_cast<int>(ENEMY::MAX) - 1; i++)
	{
		for (Enemy* EnemyObject : m_Enemys[i])
		{
			// null�`�F�b�N
			if (EnemyObject == nullptr) continue;

			EnemyObject->Unit();
		}
	}
}

void EnemyManager::Update(const float& deltaTime)
{
	// ���ݕێ����Ă���S�Ă�Enemy�̍X�V
	for (int i = 0; i < static_cast<int>(ENEMY::MAX) - 1; i++)
	{
		for (Enemy* EnemyObject : m_Enemys[i])
		{
			// �g�p�s��
			if (EnemyObject == nullptr) continue;
			if (!EnemyObject->GetEnable()) continue;

			EnemyObject->Update(deltaTime);
		}
	}
}

void EnemyManager::Draw(const XMFLOAT2& pos)
{
	// ���ݕێ����Ă���S�Ă�Enemy�̕`��
	for (int i = 0; i < static_cast<int>(ENEMY::MAX) - 1; i++)
	{
		for (Enemy* EnemyObject : m_Enemys[i])
		{
			// �g�p�s��
			if (EnemyObject == nullptr) continue;
			if (!EnemyObject->GetEnable()) continue;

			EnemyObject->Draw(pos);
		}
	}
}

void EnemyManager::CreateEnemy(const ENEMY& type,const XMFLOAT2& pos)
{
	// ���p�\�ȓG�������炻�̒l��Ԃ�
	for (Enemy* EnemyObject : m_Enemys[static_cast<int>(type) - 1])
	{
		// ���p�s��
		if (EnemyObject == nullptr) continue;
		if (EnemyObject->GetEnable()) continue;

		// ���p�\
		EnemyObject->SetEnemyPos(pos);

		return;
	}
	// ���p�\�ȓG�����Ȃ�������V��������
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
			// �����������玟��
			if (EnemyObject == nullptr) continue;

			if (!EnemyObject->GetEnable()) continue;

			vector.emplace_back(EnemyObject);
		}
	}
	return !vector.empty();
}
