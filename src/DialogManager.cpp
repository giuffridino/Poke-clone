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
    if (!m_bCloseDialog)
    {
        m_animTextCounter++;
        TheCameraManager::Instance()->endCameraMode();
        TheTextureManager::Instance()->drawFrame("sign-dialog", 0, Constants::windowHeight - 181, 1200, 181, 0, 0);
        m_strings.clear();
        m_strings.shrink_to_fit();
        splitDialog(m_strings, replaceWithNewLineChar(m_text, m_numNewLines), std::string("@@"));
        handleInput();
        DrawTextEx(m_font, TextSubtext(m_strings[m_rowTextCounter].c_str(), 0, m_animTextCounter / 4), {(float)m_dialogX, (float)m_dialogY}, m_dialogFontSize, -2, WHITE);
        // TheTextureManager::Instance()->drawFrame("animated-arrow", temp_x, temp_y, 21, 16, 0, 0);
        drawAnimatedArrow();
        TheCameraManager::Instance()->beginCameraMode();
    }
    m_bDrawDialogLater = false;
}

void DialogManager::drawDialogLater(std::string text)
{
    // std::cout << text << " " << m_text;
    if ((text != m_text) | (IsKeyPressed(KEY_X) && m_bCloseDialog))
    {
        resetDialogVariables();
        // std::cout << text << " " << m_text << "\n";
        m_bCloseDialog = false;
        m_text = text;
    }
    m_bDrawDialogLater = true;
}

void DialogManager::drawAnimatedArrow(void)
{
    if (m_strings.size() > (unsigned int) 1 && (unsigned int)m_rowTextCounter < m_strings.size() - 1 && (unsigned int) m_animTextCounter / 4 > m_strings[m_rowTextCounter].size())
    {
        Vector2 arrowPos = findArrowPos();
        TheTextureManager::Instance()->drawFrame("animated-arrow", arrowPos.x, arrowPos.y, 40, 29, 0, m_arrowFrame);
        m_arrowCounter++;
        m_arrowFrame = ((m_arrowCounter + 1) / 4) % 5;
        // std::cout << m_arrowFrame << "\n";
    }
    
}

Vector2 DialogManager::findArrowPos(void)
{
    return {(float) m_strings[m_rowTextCounter].size() * 30, (float) (m_dialogY + 10 + m_numNewLines * 50)};
}

void DialogManager::handleInput(void)
{
    // std::cout << "handling input in DialogManager\n";    
    if (IsKeyUp(KEY_X) && (unsigned int) m_animTextCounter / 4 > m_strings[m_rowTextCounter].size())
    {
        m_bKeyReleased = true;
    }
    if (IsKeyDown(KEY_X))
    {
        m_animTextCounter += 4;
        // std::cout << m_animTextCounter/4 << " " << m_strings[m_rowTextCounter].size() << "\n";
        // std::cout << "m_rowTextCounter: " << m_rowTextCounter << " m_strings[m_rowTextCounter].size(): " << m_strings[m_rowTextCounter].size() <<"\n";
        // std::cout << " m_animTextCounter: " << m_animTextCounter << " m_strings[m_rowTextCounter].size(): " << m_strings[m_rowTextCounter].size() << " m_bKeyReleased: " << m_bKeyReleased << "\n";
        if ((unsigned int) m_animTextCounter / 4 > m_strings[m_rowTextCounter].size() && m_bKeyReleased)
        {
            // std::cout << "updating rowTextCounter\n";
            int prev_rowTextCounter = m_rowTextCounter;
            m_rowTextCounter = std::min((int) m_strings.size() - 1, m_rowTextCounter + 1);
            if (prev_rowTextCounter != m_rowTextCounter) 
            {
                m_animTextCounter = 0;
            }
            // m_animTextCounter = ((unsigned int) m_rowTextCounter == m_strings.size() - 1) ? m_animTextCounter : 0;
            // std::cout << " m_animTextCounter: " << m_animTextCounter << " m_strings[m_rowTextCounter].size(): " << m_strings[m_rowTextCounter].size() <<"\n";
            if ((unsigned int) m_rowTextCounter == m_strings.size() - 1 && (unsigned int) m_animTextCounter / 4 > m_strings[m_rowTextCounter].size()) 
            {
                std::cout << "Closing dialog\n";
                m_bCloseDialog = true;
                // closeDialog();
            }
        }
        m_bKeyReleased = false;
        // std::cout << m_bKeyReleased << "\n";
    }
    // if (IsKeyDown(KEY_SPACE))
    // {
    //     m_animTextCounter += 4;
    // }
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
    // if(IsKeyDown(KEY_Q))
    // {
    //     tempFontSize -= 1;
    // }
    // if(IsKeyDown(KEY_E))
    // {
    //     tempFontSize += 1;
    // }
    // if(IsKeyDown(KEY_Z))
    // {
    //     temp_spacing -= 1;
    // }
    // if(IsKeyDown(KEY_X))
    // {
    //     temp_spacing += 1;
    // }
    // std::cout << "temp_x: " << temp_x << " temp_y: " << temp_y << " tempFontSize" << tempFontSize << " temp_spacing" << temp_spacing << "\n";
}

void DialogManager::splitDialog(std::vector<std::string> &result, const std::string &input, const std::string &separator)
{
    int startIndex = 0, endIndex = 0;
    for (unsigned int i = 0; i <= input.size(); i++) {
        // If we reached the end of the word or the end of the input.
        if ((input.substr(i, separator.size()) == separator) || (i == input.size())) {
            endIndex = i;
            std::string temp;
            temp.append(input, startIndex, endIndex - startIndex);
            result.push_back(temp);
            startIndex = endIndex + separator.size();
        }
    }
}

void DialogManager::resetDialogVariables(void)
{
    m_animTextCounter = 0; 
    m_rowTextCounter = 0; 
    m_text = ""; 
    m_numNewLines = 0;
    m_arrowFrame = 0;
    m_arrowCounter = 0;
}