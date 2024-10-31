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

// �O���錾
class Camera;
class Enemy;

class EnemyManager final
{
private:
	std::list<Enemy*> m_Enemys[static_cast<int>(ENEMY::MAX) - 1] = { {} };			// ���������G

public:
	~EnemyManager();
	void Unit();
	void Update(const float& deltaTime);
	void Draw(const XMFLOAT2& pos);
	void CreateEnemy(const ENEMY& type, const XMFLOAT2& pos);

	// �L���ł���S�Ă�Enemy���擾
	bool GetEnableEnemyObjects(std::vector<Enemy*>& vector);
};