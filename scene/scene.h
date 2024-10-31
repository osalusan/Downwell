#pragma once
// �O���錾
class Map;

class Scene
{
protected:
	Map* m_Map = nullptr; // GameScene�ŃC���X�^���X��

	float m_GoalLine = 0;
public:
	virtual ~Scene();
	virtual void Init() = 0;
	virtual void Unit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �}�b�v�̎擾
	Map* GetMap()
	{
		return m_Map;
	}

	// ���[�J���ϐ��������ɓ���܂�
	void SetGoalPosY(float goalPos)
	{
		m_GoalLine = goalPos;
	}
};