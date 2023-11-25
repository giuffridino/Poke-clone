#include "DialogManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
// #include "raylib.h"
#include "Constants.h"
#include <iostream>

DialogManager* DialogManager::s_pInstance = nullptr;

DialogManager::DialogManager(void)
{
    m_font = LoadFont("assets/custom-poke-font.png");
}

DialogManager::~DialogManager(void)
{
    UnloadFont(m_font);
}

void DialogManager::drawDialog(void)
{
    // std::cout << "Drawing dialog\n";
    m_textCounter++;
    TheCameraManager::Instance()->endCameraMode();
    TheTextureManager::Instance()->drawFrame("sign-dialog", 0, Constants::windowHeight - 181, 1200, 181, 0, 0);
    handleInput();
    DrawTextEx(m_font, TextSubtext(replaceWithNewLineChar(m_text).c_str(), 0, m_textCounter / 4), {(float)temp_x, (float)temp_y}, tempFontSize, -2, WHITE);
    // DrawTextEx(m_font, "PALLET TOWN\nShades of your journey await!", {(float)temp_x, (float)temp_y}, tempFontSize, -2, WHITE);
    TheCameraManager::Instance()->beginCameraMode();
    m_bDrawDialogLater = false;
}

void DialogManager::drawDialogLater(std::string text)
{
    m_bDrawDialogLater = true;
    m_text = text;
}

void DialogManager::handleInput(void)
{
    // std::cout << "handling input in DialogManager\n";
    if(IsKeyDown(KEY_A))
    {
        temp_x -= 1;
    }
    if(IsKeyDown(KEY_D))
    {
        temp_x += 1;
    }
    if(IsKeyDown(KEY_W))
    {
        temp_y -= 1;
    }
    if(IsKeyDown(KEY_S))
    {
        temp_y += 1;
    }
    if(IsKeyDown(KEY_Q))
    {
        tempFontSize -= 1;
    }
    if(IsKeyDown(KEY_E))
    {
        tempFontSize += 1;
    }
    if(IsKeyDown(KEY_Z))
    {
        temp_spacing -= 1;
    }
    if(IsKeyDown(KEY_X))
    {
        temp_spacing += 1;
    }
    if (IsKeyDown(KEY_SPACE))
    {
        m_textCounter += 4;
    }
    
    // std::cout << "temp_x: " << temp_x << " temp_y: " << temp_y << " tempFontSize" << tempFontSize << " temp_spacing" << temp_spacing << "\n";
}