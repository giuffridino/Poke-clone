#include "CameraManager.h"
#include "Game.h"

CameraManager* CameraManager::s_pInstance = 0;

CameraManager::CameraManager(void)
{
    m_camera.offset = {(float)TheGame::Instance()->getGameWidth() / 2, (float)TheGame::Instance()->getGameHeight()/2};
    m_camera.zoom = 5.0f;
    m_camera.rotation = 0.0f;
}

void CameraManager::setCameraTarget(Vector2 pos)
{
    m_camera.target = {pos.x + 8, pos.y + 8};
}
