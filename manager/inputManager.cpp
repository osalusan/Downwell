#include "manager/inputManager.h"
#include "DxLib.h"

// �����Ă����
bool InputManager::GetKeyPress(const int& keyCord)
{
    return CheckHitKey(keyCord);
}
