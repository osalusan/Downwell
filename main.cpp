#include "main.h"
#include <DirectXPackedVector.h>
#include <DirectXMath.h>
#include <string>
#include "manager/sceneManager.h"

#define g_DELTATIME_MAX (0.2f)
static float g_DeltaTime;

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	ChangeWindowMode(true);//��S��ʂɃZ�b�g

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGET, 32);//��ʃT�C�Y�w��

	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	SetWaitVSyncFlag(false); // ���������𖳌��ɂ���
	SetAlwaysRunFlag(true);  // ��A�N�e�B�u��Ԃł������悤�ɂ���

	static unsigned int currentTime = 0;
	static unsigned int startTime = 0;
	// �t���[�����[�g�̐F
	unsigned int Cr = GetColor(255, 255, 255);

	// �V�[���̏�����
	SceneManager::Init();

	// �����^�C���̐ݒ�
	startTime = static_cast<int>(GetNowHiPerformanceCount());

	/*** ���[�v���� ***/
	while (ProcessMessage() == 0)

	{
		currentTime = static_cast<int>(GetNowHiPerformanceCount());
		// FPS���
		if ((currentTime - startTime) >= 1000000 / 60)
		{
			g_DeltaTime = (currentTime - startTime) / 1000000.0f;

			// deltaTime�̏��
			if (g_DeltaTime >= g_DELTATIME_MAX)
			{
				g_DeltaTime = 0.0f;
			}

			startTime = currentTime;

			const int& fps = static_cast<int>(GetFPS());

			// �X�V����
			{
				// �V�[���̍X�V
				SceneManager::Update();
			}

			// �`�揈��
			{
				ClearDrawScreen();
				SetDrawScreen(DX_SCREEN_BACK);
				#if _DEBUG
				// FPS�̕`��
				std::string fpsString = "FPS:" + std::to_string(fps);
				DrawString(0, 0, fpsString.c_str(), Cr);
				#endif

				// �V�[���̕`��
				SceneManager::Draw();

				ScreenFlip();

			}
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break; 	// Escape�L�[���������烋�[�v�𔲂���	
	}

	// �V�[���̏I������
	SceneManager::Unit();

	// �摜�̃f�[�^�̑S���
	InitGraph();

	// ���f�[�^�̑S�J��
	InitSoundMem();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}
// DeltaTime���擾
float GetDeltaTime()
{
	return g_DeltaTime;
}
