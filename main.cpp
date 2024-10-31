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
	ChangeWindowMode(true);//非全画面にセット

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGET, 32);//画面サイズ指定

	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	SetWaitVSyncFlag(false); // 垂直同期を無効にする
	SetAlwaysRunFlag(true);  // 非アクティブ状態でも動くようにする

	static unsigned int currentTime = 0;
	static unsigned int startTime = 0;
	// フレームレートの色
	unsigned int Cr = GetColor(255, 255, 255);

	// シーンの初期化
	SceneManager::Init();

	// 初期タイムの設定
	startTime = static_cast<int>(GetNowHiPerformanceCount());

	/*** ループ処理 ***/
	while (ProcessMessage() == 0)

	{
		currentTime = static_cast<int>(GetNowHiPerformanceCount());
		// FPS上限
		if ((currentTime - startTime) >= 1000000 / 60)
		{
			g_DeltaTime = (currentTime - startTime) / 1000000.0f;

			// deltaTimeの上限
			if (g_DeltaTime >= g_DELTATIME_MAX)
			{
				g_DeltaTime = 0.0f;
			}

			startTime = currentTime;

			const int& fps = static_cast<int>(GetFPS());

			// 更新処理
			{
				// シーンの更新
				SceneManager::Update();
			}

			// 描画処理
			{
				ClearDrawScreen();
				SetDrawScreen(DX_SCREEN_BACK);
				#if _DEBUG
				// FPSの描画
				std::string fpsString = "FPS:" + std::to_string(fps);
				DrawString(0, 0, fpsString.c_str(), Cr);
				#endif

				// シーンの描画
				SceneManager::Draw();

				ScreenFlip();

			}
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break; 	// Escapeキーを押したらループを抜ける	
	}

	// シーンの終了処理
	SceneManager::Unit();

	// 画像のデータの全解放
	InitGraph();

	// 音データの全開放
	InitSoundMem();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
// DeltaTimeを取得
float GetDeltaTime()
{
	return g_DeltaTime;
}
