#include "GameOverState.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "Game.h"
#include "TextureManager.h"
#include "LoaderParams.h"
#include "MenuButton.h"
#include "StateParser.h"
#include <iostream>

GameState *GameOverState::s_pTransitionState = nullptr;
const std::string GameOverState::s_gameOverID = "GAMEOVER";

// GameOverState::GameOverState() : s_gameOverID("GAMEOVER")
// {
    
// }

void GameOverState::s_gameOverToMain()
{
    // Game::Instance()->getGameStateMachine()->changeState(new MainMenuState());
    s_pTransitionState = new MainMenuState();
}

void GameOverState::s_restartPlay()
{
    // Game::Instance()->getGameStateMachine()->changeState(new PlayState());
    s_pTransitionState = new PlayState();
}

void GameOverState::update()
{    
    if (m_bLoadingComplete && !m_gameObjects.empty())
    {
        for (unsigned int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->update();
        }
    }
    if (s_pTransitionState != nullptr)
    {
        TheGame::Instance()->getGameStateMachine()->changeState(s_pTransitionState);
    }
}

void GameOverState::render()
{
    if (m_bLoadingComplete && !m_gameObjects.empty())
    {
        for (unsigned int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool GameOverState::onEnter()
{
    s_pTransitionState = nullptr;
    StateParser stateParser;
    stateParser.parseState("src/assets/attack.xml", s_gameOverID, &m_gameObjects, &m_textureIDs);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);
    setCallbacks(m_callbacks);
    m_bLoadingComplete = true;
    std::cout << "Entering GameOverState\n";
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
    for (unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

bool GameOverState::onExit()
{
    if (m_bLoadingComplete && !m_gameObjects.empty())
    {
        for (unsigned int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->clean();
        }
        m_gameObjects.clear();
    }
    for (unsigned int i = 0; i < m_textureIDs.size(); i++)
    {
        TextureManager::Instance()->unload(m_textureIDs[i]);
    }

    std::cout << "exiting GameOverState\n";
    return true;
}