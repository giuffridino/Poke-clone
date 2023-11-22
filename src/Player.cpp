#include "Player.h"
#include "TextureManager.h"
#include "Constants.h"

Player::Player()
{
    TheTextureManager::Instance()->load("assets/trainer-character.png", "main-trainer");
    TheTextureManager::Instance()->load("assets/trainer-character.png", "trainer");
}

Player::~Player()
{
    TheTextureManager::Instance()->unload("main-trainer");
    TheTextureManager::Instance()->unload("trainer");
}

void Player::load(const std::unique_ptr<LoaderParams> &pParams)
{
    TrainerObject::load(std::move(pParams));
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
        case SOUTH: m_position.y += m_speed; m_animRow = 0; break;
        case NORTH: m_position.y -= m_speed; m_animRow = 1; break;
        case WEST: m_position.x -= m_speed; m_animRow = 2; break;
        case EAST: m_position.x += m_speed; m_animRow = 3; break;
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
    // std::cout << "m_position.x: " << m_position.x << "\n";
    // std::cout << "m_position.y: " << m_position.y << "\n";
    // std::cout << "m_frameWidth: " << m_frameWidth << "\n";
    // std::cout << "m_frameHeight: " << m_frameHeight << "\n";
    // std::cout << "textureID: " << m_textureID << "\n";
    // std::cout << "numFrames: " << m_animNumFrames << "\n";
    // std::cout << "m_animRow: " << m_animRow << "\n";
    // std::cout << "m_animFrame: " << m_animFrame << "\n";
    // TheTextureManager::Instance()->drawFrame("player", 64, 64, 16, 32, 1, 1, Vector2{0.0f, 0.0f});
    TheTextureManager::Instance()->drawFrame(m_textureID, m_position.x, m_position.y, m_frameWidth, m_frameHeight, m_animRow, m_animFrame, Vector2{0.0f, 0.0f});
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


