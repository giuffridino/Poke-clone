#pragma once
#ifndef __DialogManager__
#define __DialogManager__

// #include "raylib.h"
#include <string>

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
private:
    DialogManager(void) {};
    ~DialogManager(void) {};
    static DialogManager* s_pInstance;

    bool m_bDrawDialogLater = false;
    std::string m_text = "";
    
};

typedef DialogManager TheDialogManager;

#endif /* defined(__DialogManager__) */