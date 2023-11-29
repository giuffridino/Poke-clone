#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "Game.h"
#include "TextureManager.h"
#include "LoaderParams.h"
#include "Player.h"
#include "TrainerObject.h"
#include "StateParser.h"
#include "MapParser.h"
#include "CameraManager.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";
PlayState::~PlayState(void)
{
    delete m_pMap;
}

void PlayState::update(void)
{
    TheCameraManager::Instance()->setCameraTarget(m_pMap->getPlayer()->getPosition());
    if(m_pMap != 0)
    {
        m_pMap->update();
    }
    // std::cout << "PlayState::update()\n";
    // if (IsKeyDown(KEY_ESCAPE))
    // {
    //     TheGame::Instance()->getGameStateMachine()->pushState(new PauseState());
    // }
    // if(TheGame::Instance()->getPlayerLives() == 0)
    // {
    //     std::cout << "getPlayerLives() == 0 \n";
    //     TheGame::Instance()->getGameStateMachine()->changeState(new GameOverState());
    // }
    
}

void PlayState::render(void)
{
    // std::cout << "PlayState::render()\n";
    if (m_bLoadingComplete)
    {
        if(m_pMap != 0)
        {
            m_pMap->render();
        }
    }
}

bool PlayState::onEnter(void)
{
    std::cout << "Trying to enter playstate\n";
    MapParser mapParser;
    m_pMap = mapParser.parseMap(TheGame::Instance()->getMapFiles()[TheGame::Instance()->getCurrentMap()].c_str());
    std::cout << "map parsed in PlayState::OnEnter\n";
    if (m_pMap)
    {
        std::cout << "m_pMap is valid\n";
        m_bLoadingComplete = true;
    } 
    std::cout << "Done with PlayState::OnEnter\n";
    return true;
}

bool PlayState::onExit(void)
{
    m_bExiting = true;
    for (unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    for (unsigned int i = 0; i < m_textureIDs.size(); i++)
    {
        TheTextureManager::Instance()->unload(m_textureIDs[i]);
    }
    std::cout << "exiting PlayState\n";
    return true;
}