#include "Player.h"
#include "TextureManager.h"
#include "Constants.h"


Player::Player()
{
    TheTextureManager::Instance()->load("assets/monkey-boy.png", "monkey-boy");
}

Player::~Player()
{
    TheTextureManager::Instance()->unload("monkey-boy");
}

void Player::update()
{
    if (m_moveTime <= 0 && !m_bIsMoving)
    {
        Direction inputDir = getInputDirection();
        if (inputDir != NONE) // Check if a direction key is pressed
        {
            m_facing = inputDir;
            m_lastFacing = m_facing;
            m_moveTime = m_framesToCrossOneTile; // Set move time for one tile movement
            m_bIsMoving = true;
        }
    }
    if ( m_moveTime > 0)
    {
        m_moveTime--;
        m_frameCounter++;
        if (m_frameCounter == 4)
        {
            m_frameCounter = 0;
            m_animFrame = (m_animFrame + 1) % m_animNumFrames;
        }
        switch (m_facing)
        {
        case NORTH: m_position.y -= m_speed; m_animRow = 4; break;
        case SOUTH: m_position.y += m_speed; m_animRow = 0; break;
        case EAST: m_position.x += m_speed; m_animRow = 6; break;
        case WEST: m_position.x -= m_speed; m_animRow = 2; break;
        default:
            break;
        }
    }
    if (m_moveTime == 0) // Reset facing direction and moving status when one tile movement is done
    {
        m_facing = NONE;
        // m_lastFacing = NONE;
        m_bIsMoving = false;
    }
}

void Player::draw()
{
    TheTextureManager::Instance()->drawFrame("monkey-boy", m_position.x, m_position.y, m_frameWidth, m_frameHeight, m_animRow, m_animFrame, Vector2{0.0f, 0.0f});
}

Direction Player::getInputDirection()
{    
    if ((m_lastFacing == EAST && IsKeyDown(KEY_RIGHT)) | (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)))
    {
        return EAST;
    }
    else if ((m_lastFacing == WEST && IsKeyDown(KEY_LEFT)) | (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)))
    {
        return WEST;
    }
    else if ((m_lastFacing == NORTH && IsKeyDown(KEY_UP)) | (IsKeyDown(KEY_UP) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN)))
    {
        return NORTH;
    }
    else if ((m_lastFacing == SOUTH && IsKeyDown(KEY_DOWN)) | (IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_RIGHT)))
    {
        return SOUTH;
    }
    return NONE;
}


