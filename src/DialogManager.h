#pragma once
#ifndef __DialogManager__
#define __DialogManager__

#include "raylib.h"
#include <string>
#include <vector>

class Font;

class DialogManager
{
public:
    static DialogManager* Instance(void)
    {
        if (s_pInstance == nullptr)
        {
            s_pInstance = new DialogManager();
        }
        return s_pInstance;        
    }

    bool getDrawDialogLater(void) { return m_bDrawDialogLater; }

    void drawDialog(void);  
    void drawDialogLater(std::string text);  
    void resetDialogVariables(void);
    void drawAnimatedArrow(void);
    Vector2 findArrowPos(void);
    void handleInput(void);
    void splitDialog(std::vector<std::string> &result, const std::string &input, const std::string &separator);
    // void closeDialog(void);
private:
    DialogManager(void);
    ~DialogManager(void);
    static DialogManager* s_pInstance;

    bool m_bDrawDialogLater = false;
    std::string m_text = "";

    Font m_font;

    int m_dialogX = 52;
    int m_dialogY = 656;
    int m_dialogFontSize = 48;
    int m_dialogSpacing = 6;
    int temp_x = 1100;
    int temp_y = 700;
    int tempFontSize = 48;
    int temp_spacing = 6;

    int m_animTextCounter = 0;
    int m_rowTextCounter = 0;
    std::vector<std::string> m_strings;
    bool m_bKeyReleased = true;
    bool m_bCloseDialog = false;

    int m_arrowFrame = 0;
    int m_arrowCounter = 0;
    int m_numNewLines = 0;
};

typedef DialogManager TheDialogManager;

#endif /* defined(__DialogManager__) */