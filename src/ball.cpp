#include "ball.h"
#include <raylib.h>

Ball::Ball() : m_x(100), m_y(100), m_speedX(0), m_speedY(0), m_radius(15)
{
    
}

void Ball::Update()
{
    m_speedX = 0;
    m_speedY = 0;
    handleInput();
    m_x += m_speedX;
    m_y += m_speedY;

    // if (m_x + m_radius >= GetScreenWidth() || m_x - m_radius <= 0)
    //     m_speedX *= -1;

    // if (m_y + m_radius >= GetScreenHeight() || m_y - m_radius <= 0)
    //     m_speedY *= -1;
}

void Ball::Draw()
{
    DrawCircle(m_x, m_y, m_radius, WHITE);
}

void Ball::handleInput()
{
    if (IsKeyDown(KEY_RIGHT) && (m_x + 2 * m_radius) <= GetScreenWidth())
    {
        m_speedX = 5;
    }
    if (IsKeyDown(KEY_LEFT) && (m_x - 2 * m_radius) >= 0)
    {
        m_speedX = -5;
    }
    if (IsKeyDown(KEY_UP) && (m_y - 2 * m_radius) >= 0)
    {
        m_speedY = -5;
    }
    if (IsKeyDown(KEY_DOWN) && (m_y + 2 * m_radius) <= GetScreenHeight())
    {
        m_speedY = 5;
    }
}