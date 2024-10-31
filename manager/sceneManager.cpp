#include "manager/sceneManager.h"
#include "manager/soundManager.h"
#include "manager/textureManager.h"
#include "scene/titleScene.h"

Scene* SceneManager::m_Scene = nullptr;
Scene* SceneManager::m_NextScene = nullptr;
Fade* SceneManager::m_Fade = nullptr;

void SceneManager::Init()
{
	if (m_Scene == nullptr)
	{
		m_Scene = new TitleScene;
	}
	if (m_Scene != nullptr)
	{
		m_Scene->Init();
	}

	if (m_Fade == nullptr)
	{
		m_Fade = new Fade;
	}
	if (m_Fade != nullptr)
	{
		m_Fade->Init();
	}

	// 一番最後に呼ぶ
	TextureManager::Init();
	SoundManager::Init();
}

void SceneManager::Unit()
{
	delete m_Fade;
	m_Fade = nullptr;

	if (m_Scene != nullptr) 
	{
		m_Scene->Unit(); 
	}

	delete m_Scene;
	m_Scene = nullptr;
}

void SceneManager::Update()
{
	if (m_Scene != nullptr)
	{
		m_Scene->Update();
	}
	if (m_Fade != nullptr)
	{
		m_Fade->Update();
	}
}

void SceneManager::Draw()
{
	if (m_Scene != nullptr)
	{
		m_Scene->Draw();
	}

	if (m_Fade != nullptr)
	{
		m_Fade->Draw();
	}
	// フェードが終わったらシーン遷移
	if (m_NextScene != nullptr)
	{
		if (m_Fade != nullptr)
		{
			m_Fade->StartFadeOut();

			if (!m_Fade->GetFadeComplete())
			{
				return;
			}
		}
		
		if (m_Scene != nullptr)
		{
			m_Scene->Unit();
		}

		delete m_Scene;
		m_Scene = nullptr;

		m_Scene = m_NextScene;

		if (m_Scene != nullptr)
		{
			m_Scene->Init();
		}

		if (m_Fade != nullptr)
		{
			m_Fade->StartFadeIn();
		}

		m_NextScene = nullptr;

		// 一番最後に呼ぶ
		TextureManager::Init();
		SoundManager::Init();
	}
}

Scene* SceneManager::GetScene()
{
	return m_Scene;
}