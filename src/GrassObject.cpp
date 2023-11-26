#include "GrassObject.h"
#include "CollisionManager.h"

GrassObject::GrassObject(void) : TrainerObject() { }

void GrassObject::load(std::unique_ptr<LoaderParams> const &pParams)
{
    TrainerObject::load((pParams));
}

void GrassObject::draw()
{
    TrainerObject::draw();
}

void GrassObject::update()
{
    if (m_bUpdating)
    {
        m_frameCounter++;
        if (m_animFrame == m_animNumFrames)
        {
            m_delay++;
            if (m_delay >= 200)
            {
                m_delay = 0;
                m_bUpdating = false;
                m_animFrame = 0;
            }
        }
        else if (m_frameCounter >= m_frameDelay)
        {
            m_frameCounter = 0;
            m_animFrame = std::min((m_animFrame + 1), m_animNumFrames);
            // m_animFrame = (m_animFrame + 1) % m_animNumFrames;
        }
    }
}

void GrassObject::performAnimation(void)
{
    
}

void GrassObject::clean()
{
}