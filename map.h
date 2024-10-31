#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "main.h"

#define STAGE_WIDTH (SCREEN_WIDTH / 2)						// �X�e�[�W�̉���
#define MAPCHIP_WIDTH (SCREEN_WIDTH * 0.045f)				// �}�b�v�`�b�v���̉���
#define MAPCHIP_HEIGHT (SCREEN_HEIGET * 0.08f)				// �}�b�v�`�b�v���̏c��	

#define MAP_NUM_MAX (5)										// �}�b�v�̍ő��搔
#define SPACE_WIDTH (MAPCHIP_WIDTH * 5.5f)					// �}�b�v�̈ʒu�𒲐�	

#define LEFT_WALL (SPACE_WIDTH + (MAPCHIP_WIDTH * 0.5f))					 // ���̕�
#define RIGHT_WALL ((SCREEN_WIDTH - SPACE_WIDTH) + (MAPCHIP_WIDTH * 0.28f))	 // �E�̕�

enum class STAGE
{
	START = 0,
	GOAL,
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5,
	STAGE6,
	STAGE7,
	STAGE8,
	STAGE9,
	STAGE10,
	MAX
};

enum class OBJECT
{
	NONE = 0,
	UNBREAK_BLOCK,
	BREAK_BLOCK,
	JELLYFISH_ENEMY,
	SNAIL_ENEMY
};

enum class LAYER {
	CAMERA = 0,
	PLAYER,
	OBJECT,
	UI,
	MAX
};

// �O���錾
class Scene;
class EnemyManager;
class BulletManager;
class BlockManager;
class Camera;
class Player;

class Map final
{
private:
	// �|�C���^�ۑ��p
	Scene* m_Scene = nullptr;
	
	// �C���X�^���X�����ĊǗ�
	BulletManager* m_BulletManager = nullptr;
	EnemyManager* m_EnemyManager = nullptr;
	BlockManager* m_BlockManager = nullptr;
	Camera* m_Camera = nullptr;
	Player* m_Player = nullptr;


	std::string m_FilePath = {};
	char m_Delim = {};

	// �X�e�[�W��ۑ�
	std::unordered_map<int ,std::vector<std::vector<OBJECT>>> m_StaePool = {};

	int m_SelectStage[MAP_NUM_MAX] = {};

	OBJECT CastCell(const std::string& cell);
	void LoadCSV(const std::string& filePath, const char& delim, const int& stageNo);
	void CreateObject(const OBJECT& objectID,const XMFLOAT2& pos);
	void LoadStage();
public:
	~Map();
	void Init();
	void Unit();
	void Update();
	void Draw();

	// �J�����̎擾
	Camera* GetCamera()
	{
		return m_Camera;
	}
	// �v���C���[�̎擾
	Player* GetPlayer()
	{
		return m_Player;
	}
	// �o���b�g�}�l�[�W���[�̎擾
	BulletManager* GetBulletManager()
	{
		return m_BulletManager;
	}
	// �G�l�~�[�}�l�[�W���[�̎擾
	EnemyManager* GetEnemymanager()
	{
		return m_EnemyManager;
	}
	// �u���b�N�}�l�[�W���[�̎擾
	BlockManager* GetBlockManager()
	{
		return m_BlockManager;
	}
};