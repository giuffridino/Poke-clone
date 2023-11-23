#include "AnimatedObject.h"


AnimatedObject::AnimatedObject(void) : TrainerObject() { }

void AnimatedObject::load(std::unique_ptr<LoaderParams> const &pParams)
{
    TrainerObject::load((pParams));
}

void AnimatedObject::draw()
{
    TrainerObject::draw();
}

void AnimatedObject::update()
{    
    // m_currentFrame = int((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames);
    // TrainerObject::update();
    m_frameCounter++;
    if (m_frameCounter >= m_frameDelay)
    {
        m_frameCounter = 0;
        m_animFrame = (m_animFrame + 1) % m_animNumFrames;
    }
    
}

void AnimatedObject::clean()
{
}