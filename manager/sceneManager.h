#pragma once
#include "fade.h"

// ‘O•ûéŒ¾
class Scene;

class SceneManager final
{
private:
	static Scene* m_Scene;
	static Scene* m_NextScene;
	static Fade* m_Fade;
public:
	static void Init();
	static void Unit();
	static void Update();
	static void Draw();
	static Scene* GetScene();


	// ƒV[ƒ“‚Ì‘JˆÚ
	template <typename T>
	static void ChangeScene()
	{
		if (m_NextScene == nullptr && m_Fade != nullptr)
		{
			m_NextScene = new T;
			m_Fade->Init();
		}
	}
};