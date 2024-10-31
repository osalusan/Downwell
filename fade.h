#pragma once
class Fade final
{
private:
	bool m_FadeIn = false;
	bool m_FadeOut = false;
	float m_CurrentTime = 0.0f;

public:
	void Init();
	void Update();
	void Draw();

	void StartFadeIn();
	void StartFadeOut();

	const bool GetFadeComplete();
};