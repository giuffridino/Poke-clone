#pragma once
#ifndef __LoaderParams__
#define __LoaderParams__

#include "raylib.h"
#include "Constants.h"
#include <iostream>

class LoaderParams
{
public:
    LoaderParams(std::string textureID = "", Vector2 m_position = {0.0f, 0.0f}, int frameWidth = 0, int frameHeight = 0, int animRow = 0, int animFrame = 0, int animNumFrames = 1, int frameCounter = 0, int frameDelay = 0, Direction facing = SOUTH, int callbackID = 0) : 
    m_textureID(textureID), 
    m_position(m_position), m_frameWidth(frameWidth), m_frameHeight(frameHeight), 
    m_animRow(animRow), m_animFrame(animFrame), m_animNumFrames(animNumFrames), m_frameCounter(frameCounter), m_frameDelay(frameDelay),
    m_facing(facing),
    m_callbackID(callbackID)
    {
    }

    std::string getTextureID(void) const { return m_textureID; }
    Vector2 getPosition(void) const { return m_position; }
    int getFrameWidth(void) const { return m_frameWidth; }
    int getFrameHeight(void) const { return m_frameHeight; }
    int getAnimRow(void) const { return m_animRow; }
    int getAnimFrame(void) const { return m_animFrame; }
    int getAnimNumFrames(void) const { return m_animNumFrames; }
    int getFrameCounter(void) const { return m_frameCounter; }
    int getFrameDelay(void) const { return m_frameDelay; }
    Direction getFacing(void) const { return m_facing; }
    int getCallbackID(void) const { return m_callbackID; }

private:
    std::string m_textureID;
    Vector2 m_position;
    int m_frameWidth, m_frameHeight;
    double m_scale, m_rotation, m_alpha;
    // RayLib_FLIP m_flip;
    int m_animRow, m_animFrame, m_animNumFrames, m_frameCounter, m_frameDelay; 
    Direction m_facing;
    int m_callbackID;
};

#endif /* defined(__LoaderParams__) */