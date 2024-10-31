#include "map.h"
#include "object/block.h"
#include "character/jellyfish.h"
#include "character/snail.h"
#include "character/player.h"
#include "camera.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>
#include "manager/sceneManager.h"
#include "manager/bulletManager.h"
#include "manager/enemyManager.h"
#include "manager/blockManager.h"
#include "gameObject.h"
#include "scene/scene.h"

Map::~Map()
{	
	delete m_Camera;
	m_Camera = nullptr;
	delete m_Player;
	m_Player = nullptr;

	delete m_BulletManager;
	m_BulletManager = nullptr;
	delete m_BlockManager;
	m_BlockManager = nullptr;
	delete m_EnemyManager;
	m_EnemyManager = nullptr;

	m_Scene = nullptr;
}

void Map::Init()
{
	// ����̃C���X�^���X���������̂݊i�[
	if (m_Scene == nullptr)
	{
		m_Scene = SceneManager::GetScene();
		if (m_Scene == nullptr) return;
	}

	// �C���X�^���X�����ȊO�ɌĂ� / �ė��p
	if (m_EnemyManager != nullptr)
	{
		m_EnemyManager->Unit();
	}
	if (m_BlockManager != nullptr)
	{
		m_BlockManager->Unit();
	}

	if (m_Player == nullptr)
	{
		// ��ԏ��߂̃I�u�W�F�N�g�Ƃ��Đ���
		m_Player = new Player;
	}
	if (m_Player != nullptr)
	{
		m_Player->Init();
	}

	if (m_Camera == nullptr)
	{
		// �v���C���[�̌�ɐ���
		m_Camera = new Camera;
	}
	if (m_Player != nullptr)
	{
		m_Camera->Init();
	}

	// �J�����̌�ɍ쐬
	if (m_EnemyManager == nullptr)
	{
		m_EnemyManager = new EnemyManager;
	}
	if (m_BlockManager == nullptr)
	{
		m_BlockManager = new BlockManager;
	}

	if (m_BulletManager == nullptr)
	{
		m_BulletManager = new BulletManager;
	}
	if (m_BulletManager != nullptr)
	{
		m_BulletManager->Init();
	}

	for (int i = 0; i < MAP_NUM_MAX; i++)
	{
		m_SelectStage[i] = 0;
	}

	// �X�e�[�W�̓ǂݍ���
	LoadStage();
	
	XMFLOAT2 Pos = { 0.0f ,0.0f };

	// �X�^�[�g�̐���
	for (const std::vector<OBJECT>& Stage : m_StaePool[static_cast<int>(STAGE::START)])
	{
		Pos.y++;
		Pos.x = 0;
		for (const OBJECT& ObjectID : Stage)
		{
			Pos.x++;
			CreateObject(ObjectID, Pos);
		}
	}

	// 5���̃X�e�[�W�������_������
	for (int StageCount = 0; StageCount < MAP_NUM_MAX; StageCount++)
	{
		const int& StageNo = m_SelectStage[StageCount];
		for (const std::vector<OBJECT>& Stage : m_StaePool[StageNo])
		{
			Pos.y++;
			Pos.x = 0;
			for (const OBJECT& ObjectID : Stage)
			{
				Pos.x++;
				CreateObject(ObjectID, Pos);
			}
		}
	}

	// �S�[���̐���
	for (const std::vector<OBJECT>& Stage : m_StaePool[static_cast<int>(STAGE::GOAL)])
	{
		Pos.y++;
		Pos.x = 0;
		for (const OBJECT& ObjectID : Stage)
		{
			Pos.x++;
			CreateObject(ObjectID, Pos);
		}
	}

	m_Scene->SetGoalPosY(MAPCHIP_HEIGHT* Pos.y);
}

void Map::Unit()
{
	// Manager�̏I������
	if (m_EnemyManager != nullptr)
	{
		m_EnemyManager->Unit();
	}
	if (m_BulletManager != nullptr)
	{
		m_BulletManager->Unit();
	}
	if (m_BlockManager != nullptr)
	{
		m_BlockManager->Unit();
	}

	if (m_Camera != nullptr)
	{
		m_Camera->Unit();
	}
	if (m_Player != nullptr)
	{
		m_Player->Unit();
	}
}

void Map::Update()
{
	const float& DeltaTime = GetDeltaTime();

	if (m_Player != nullptr)
	{
		m_Player->Update(DeltaTime);
	}
	if (m_Camera != nullptr)
	{
		m_Camera->Update(DeltaTime);
	}

	// Manager�̍X�V
	if (m_EnemyManager != nullptr)
	{
		m_EnemyManager->Update(DeltaTime);
	}
	if (m_BulletManager != nullptr)
	{
		m_BulletManager->Update(DeltaTime);
	}
	if (m_BlockManager != nullptr)
	{
		m_BlockManager->Update(DeltaTime);
	}
}

void Map::Draw()
{
	if (m_Camera == nullptr) return;

	const XMFLOAT2& CameraPos = m_Camera->GetPos();

	if (m_Player != nullptr)
	{
		m_Player->Draw(CameraPos);
	}

	// Manager�̕`��
	if (m_EnemyManager != nullptr)
	{
		m_EnemyManager->Draw(CameraPos);
	}
	if (m_BulletManager != nullptr)
	{
		m_BulletManager->Draw(CameraPos);
	}
	if (m_BlockManager != nullptr)
	{
		m_BlockManager->Draw(CameraPos);
	}
}

// int�ɕϊ�
OBJECT Map::CastCell(const std::string& cell)
{
	return static_cast<OBJECT>(stoi(cell));
}

// CSV�t�@�C����ǂݍ��݁Am_Cell�ɕۑ�
void Map::LoadCSV(const std::string& filePath, const char& delim, const int& stageNo)
{
	m_FilePath = filePath;
	m_Delim = delim;

	std::string Str_Buf = {};
	std::string Str_Comma_Buf = {};

	std::ifstream Ifs_CsvFile(filePath);

	std::vector<std::vector<OBJECT>> Stage = {};

	// getline�֐���1�s���ǂݍ���(�ǂݍ��񂾓��e�� str_buf �Ɋi�[)
	for (int i = 0; getline(Ifs_CsvFile, Str_Buf); i++)
	{
		Stage.emplace_back(std::vector<OBJECT>());

		// delim ��؂育�ƂɃf�[�^��ǂݍ��ނ��߂� istringstream �ɂ���
		std::istringstream i_stream(Str_Buf);

		for (int j = 0; getline(i_stream, Str_Comma_Buf, delim); j++)
		{
			if (Str_Comma_Buf == "") Str_Comma_Buf = "0";

			Stage.at(i).push_back(CastCell(Str_Comma_Buf));

		}
	}

	m_StaePool.emplace(stageNo, Stage);
}

void Map::CreateObject(const OBJECT& objectID, const XMFLOAT2& pos)
{
	if (m_Scene == nullptr || m_EnemyManager == nullptr) return;

	const XMFLOAT2& POS = { (MAPCHIP_WIDTH * pos.x) + SPACE_WIDTH , MAPCHIP_HEIGHT * pos.y };

	switch (objectID)
	{
	case OBJECT::UNBREAK_BLOCK:		// ���Ȃ��u���b�N
		m_BlockManager->CreateBlock(BLOCK::UNBREAK, POS);
		break;
	case OBJECT::BREAK_BLOCK:		// ����u���b�N
		m_BlockManager->CreateBlock(BLOCK::BREAK, POS);
		break;
	case OBJECT::JELLYFISH_ENEMY:	// ���V����G
		m_EnemyManager->CreateEnemy(ENEMY::JELLYFISH,POS);
		break;
	case OBJECT::SNAIL_ENEMY:		// �n�𔇂��G
		m_EnemyManager->CreateEnemy(ENEMY::SNAIL,POS);
		break;
	default:
		break;
	}
}

// start��goal�ȊO�̓ǂݍ��ݏ���
void Map::LoadStage()
{
	// �X�^�[�g�S�[���̍쐬
	LoadCSV("asset\\stage\\start.csv", ',', static_cast<int>(STAGE::START));
	LoadCSV("asset\\stage\\goal.csv", ',', static_cast<int>(STAGE::GOAL));

	// �����̐���
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(static_cast<int>(STAGE::STAGE1), static_cast<int>(STAGE::MAX) - 1);

	const std::string& StagePath = "asset\\stage\\stage";
	const std::string& FileType = ".csv";

	for (int StageCount = 0; StageCount < MAP_NUM_MAX; StageCount++)
	{
		const int& StageNo = dis(gen);
		m_SelectStage[StageCount] = StageNo;

		// �܂��ǂݍ��݂���Ă��Ȃ�������
		if (m_StaePool.count(StageNo) == 0)
		{
			const std::string& StageName = StagePath + std::to_string(StageNo) + FileType;
			LoadCSV(StageName, ',', StageNo);	
		}
	}
}

