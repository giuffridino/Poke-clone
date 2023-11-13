#pragma once

class Ball
{
public:
    Ball();
    void Update();
    void Draw();
    void handleInput();

private:
    int m_x;
    int m_y;
    int m_speedX;
    int m_speedY;
    int m_radius;
};