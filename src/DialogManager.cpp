#include "DialogManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "raylib.h"
#include <iostream>

DialogManager* DialogManager::s_pInstance = nullptr;

void DialogManager::drawDialog(void)
{
    // std::cout << "Drawing dialog\n";
    TheCameraManager::Instance()->endCameraMode();
    TheTextureManager::Instance()->drawFrame("dialog", 0, 619, 1200, 181, 0, 0);
    TheCameraManager::Instance()->beginCameraMode();
    m_bDrawDialogLater = false;
}

void DialogManager::drawDialogLater(std::string text)
{
    m_bDrawDialogLater = true;
    m_text = text;
}