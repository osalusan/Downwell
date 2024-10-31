#pragma once
#include "DxLib.h"
#include <DirectXMath.h>
using namespace DirectX;

#if _DEBUG 
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGET (720)
#else
#define SCREEN_WIDTH (1920)
#define SCREEN_HEIGET (1080)
#endif

#define SHOW_COLLISION (true)

float GetDeltaTime();
