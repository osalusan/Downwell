#pragma once
#include <list>
#include <vector>
#include "main.h"
enum class ENEMY
{
	NONE = 0,
	JELLYFISH,
	SNAIL,
	MAX
};

// ‘O•ûéŒ¾
class Camera;
class Enemy;

class EnemyManager final
{
private:
	std::list<Enemy*> m_Enemys[static_cast<int>(ENEMY::MAX) - 1] = { {} };			// ¶¬‚µ‚½“G

public:
	~EnemyManager();
	void Unit();
	void Update(const float& deltaTime);
	void Draw(const XMFLOAT2& pos);
	void CreateEnemy(const ENEMY& type, const XMFLOAT2& pos);

	// —LŒø‚Å‚ ‚é‘S‚Ä‚ÌEnemy‚ğæ“¾
	bool GetEnableEnemyObjects(std::vector<Enemy*>& vector);
};