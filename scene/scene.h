#pragma once
// 前方宣言
class Map;

class Scene
{
protected:
	Map* m_Map = nullptr; // GameSceneでインスタンス化

	float m_GoalLine = 0;
public:
	virtual ~Scene();
	virtual void Init() = 0;
	virtual void Unit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// マップの取得
	Map* GetMap()
	{
		return m_Map;
	}

	// ローカル変数を引数に入れます
	void SetGoalPosY(float goalPos)
	{
		m_GoalLine = goalPos;
	}
};