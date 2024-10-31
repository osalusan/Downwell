#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "main.h"

#define STAGE_WIDTH (SCREEN_WIDTH / 2)						// ステージの横幅
#define MAPCHIP_WIDTH (SCREEN_WIDTH * 0.045f)				// マップチップ一つ一つの横幅
#define MAPCHIP_HEIGHT (SCREEN_HEIGET * 0.08f)				// マップチップ一つ一つの縦幅	

#define MAP_NUM_MAX (5)										// マップの最大区画数
#define SPACE_WIDTH (MAPCHIP_WIDTH * 5.5f)					// マップの位置を調整	

#define LEFT_WALL (SPACE_WIDTH + (MAPCHIP_WIDTH * 0.5f))					 // 左の壁
#define RIGHT_WALL ((SCREEN_WIDTH - SPACE_WIDTH) + (MAPCHIP_WIDTH * 0.28f))	 // 右の壁

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

// 前方宣言
class Scene;
class EnemyManager;
class BulletManager;
class BlockManager;
class Camera;
class Player;

class Map final
{
private:
	// ポインタ保存用
	Scene* m_Scene = nullptr;
	
	// インスタンス化して管理
	BulletManager* m_BulletManager = nullptr;
	EnemyManager* m_EnemyManager = nullptr;
	BlockManager* m_BlockManager = nullptr;
	Camera* m_Camera = nullptr;
	Player* m_Player = nullptr;


	std::string m_FilePath = {};
	char m_Delim = {};

	// ステージを保存
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

	// カメラの取得
	Camera* GetCamera()
	{
		return m_Camera;
	}
	// プレイヤーの取得
	Player* GetPlayer()
	{
		return m_Player;
	}
	// バレットマネージャーの取得
	BulletManager* GetBulletManager()
	{
		return m_BulletManager;
	}
	// エネミーマネージャーの取得
	EnemyManager* GetEnemymanager()
	{
		return m_EnemyManager;
	}
	// ブロックマネージャーの取得
	BlockManager* GetBlockManager()
	{
		return m_BlockManager;
	}
};