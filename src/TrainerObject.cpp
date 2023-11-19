#include "TrainerObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"

TrainerObject::TrainerObject(void) : GameObject()
{
    
}

void TrainerObject::load(const std::unique_ptr<LoaderParams> &pParams)
{
    m_textureID = pParams->getTextureID();
    m_position = pParams->getPosition();
    m_frameWidth = pParams->getFrameWidth();
    m_frameHeight = pParams->getFrameHeight();
    m_animRow = pParams->getAnimRow();
    m_animFrame = pParams->getAnimFrame();
    m_animNumFrames = pParams->getAnimNumFrames();
    m_frameCounter = pParams->getFrameCounter();
    m_frameDelay = pParams->getFrameDelay();
}

void TrainerObject::draw(void)
{
    TheTextureManager::Instance()->drawFrame(m_textureID, m_position.x, m_position.y, m_frameWidth, m_frameHeight, m_animRow, m_animFrame);
}

void TrainerObject::update(void)
{
    
}