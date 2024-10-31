#include "manager/inputManager.h"
#include "DxLib.h"

// ‰Ÿ‚µ‚Ä‚¢‚éŠÔ
bool InputManager::GetKeyPress(const int& keyCord)
{
    return CheckHitKey(keyCord);
}
