#include "MenuButton.h"
#include "LoaderParams.h"
// #include "InputHandler.h"
#include "raylib.h"

MenuButton::MenuButton(void) : TrainerObject(), m_callback(0)
{
    m_animFrame = MOUSE_OUT;
}

void MenuButton::load(const std::unique_ptr<LoaderParams> &pParams)
{
    m_position = pParams -> getPosition();
    m_frameWidth = pParams -> getFrameWidth();
    m_frameHeight = pParams -> getFrameHeight();
    m_textureID = pParams -> getTextureID();
    m_animNumFrames = pParams -> getAnimNumFrames();
    m_animRow = 0;
    m_animFrame = MOUSE_OUT;
    m_animNumFrames = pParams -> getAnimNumFrames();
    m_callbackID = pParams -> getCallbackID();
    m_frameDelay = pParams -> getFrameDelay();
}

void MenuButton::draw(void)
{
    TrainerObject::draw();
}

void MenuButton::update(void)
{
    TrainerObject::update();
    Vector2 pMousePos = GetMousePosition();
    if (pMousePos.x < (m_position.x + m_frameWidth) 
    && pMousePos.x > m_position.x
    && pMousePos.y < (m_position.y + m_frameHeight)
    && pMousePos.y > m_position.y)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_bReleased)
        {
            m_animFrame = CLICKED;
            // std::cout << "Button clicked, calling callback function m_callback = " << m_callback <<"\n";
            if (m_callback)
            {
                // std::cout << "m_callback is  defined\n";
                m_callback();
            }
            // std::cout << "After if(!m_callback)\n";
            m_bReleased = false;
        }
        else if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))
        {
            m_animFrame = MOUSE_OVER;
            m_bReleased = true;
        }   
    }
    else
    {
        m_animFrame = MOUSE_OUT;
    }
    
}

void MenuButton::clean(void)
{
    TrainerObject::clean();
}