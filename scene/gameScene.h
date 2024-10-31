#pragma once
#include "scene/scene.h"
#include <string>

// ‘O•ûéŒ¾
class UI;
class GameOver;
class Player;

class GameScene final :public Scene
{
private:
	UI* m_UI = nullptr;
	GameOver* m_GameOver = nullptr;
	Player* m_PlayerCache = nullptr;
	int m_StageNo = 0;
	std::string m_StageNoString = {};

	bool m_ChangeScene = false;

	void ChangeGameOver();
public:
	virtual ~GameScene()override;
	virtual void Init()override;
	virtual void Unit()override;
	virtual void Update()override;
	virtual void Draw()override;	
};