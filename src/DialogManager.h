#pragma once
#ifndef __DialogManager__
#define __DialogManager__

#include "raylib.h"
#include <string>

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
    void handleInput(void);
private:
    DialogManager(void);
    ~DialogManager(void);
    static DialogManager* s_pInstance;

    bool m_bDrawDialogLater = false;
    std::string m_text = "";

    Font m_font;

    int temp_x = 52;
    int temp_y = 656;
    int tempFontSize = 48;
    int temp_spacing = 6;
    
};

typedef DialogManager TheDialogManager;

#endif /* defined(__DialogManager__) */