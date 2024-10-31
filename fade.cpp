#include "fade.h"
#include "manager/textureManager.h"
#include "main.h"

// フェードの最大時間
constexpr float m_FADE_MAX = 1.0f;

void Fade::Init()
{
	m_FadeIn = false;
	m_FadeOut = false;
	m_CurrentTime = 0.0f;
}

void Fade::Update()
{
	if (!m_FadeIn && !m_FadeOut) return ;

	if (m_FadeOut)
	{
		m_CurrentTime += GetDeltaTime();
	}
	else if (m_FadeIn)
	{
		m_CurrentTime -= GetDeltaTime();
	}
}

void Fade::Draw()
{
	const int& Alfa = static_cast<int>(m_CurrentTime * 255.0f);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alfa);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGET, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Fade::StartFadeIn()
{
	if (m_FadeIn || m_FadeOut) return;
	m_FadeIn = true;
	m_CurrentTime = 1.0f;
}

void Fade::StartFadeOut()
{
	if (m_FadeIn || m_FadeOut) return;
	m_FadeOut = true;
	m_CurrentTime = 0.0f;
}

const bool Fade::GetFadeComplete()
{
	if (!m_FadeIn && !m_FadeOut) return false;

	if (m_CurrentTime < m_FADE_MAX && m_FadeOut)
	{
		return false;
	}
	if (m_CurrentTime > 0 && m_FadeIn)
	{
		return false;
	}

	m_FadeIn = false;
	m_FadeOut = false;
	m_CurrentTime = 0.5f;
	return true;
}
