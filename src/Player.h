#pragma once
#ifndef __Player__
#define __Player__

#include <raylib.h>

enum Direction { NONE, NORTH, SOUTH, EAST, WEST };

class Player
{
public:
    Player();
    ~Player();
    void update();
    void draw();
    void handleInput();

    Direction getInputDirection();

private:
    Texture2D m_texture;
    Vector2 m_position = {0.0f, 0.0f};
    Vector2 m_velocity = {0.0f, 0.0f};
    Vector2 m_direction = {0.0f, 0.0f};
    Vector2 m_offset = {0.0f, 0.0f};
    bool m_bIsMoving = false;

    const int m_frameWidth = 16;
    const int m_frameHeight = 16;
    int m_animRow = 0;
    int m_animFrame = 0;
    int m_animNumFrames = 4;
    int m_frameDelay = 10;
    int m_frameCounter = 0;

    Direction m_facing = SOUTH;
    Direction m_lastFacing = SOUTH;
    int m_moveTime = 0;
    int m_framesToCrossOneTile = 8;
    int m_speed = 64 / m_framesToCrossOneTile;

};

#endif /* defined(__Player__) */