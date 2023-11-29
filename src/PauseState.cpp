#include "PauseState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "LoaderParams.h"
// #include "InputHandler.h"
#include "StateParser.h"

GameState *PauseState::s_pTransitionState = nullptr;
const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update(void)
{
    if (m_bLoadingComplete && !m_gameObjects.empty())
    {
        for (unsigned int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->update();
        }
    }
    if (s_pTransitionState)
    {
        Game::Instance()->getGameStateMachine()->changeState(s_pTransitionState);
    }
    // Game::Instance()->getGameStateMachine()->dequeState();
}

void PauseState::render(void)
{
    if (m_bLoadingComplete && !m_gameObjects.empty())
    {
        for (unsigned int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->draw();
        }
    }
}

bool PauseState::onEnter(void)
{
    s_pTransitionState = nullptr;
    StateParser stateParser;
    stateParser.parseState("assets/attack.xml", s_pauseID, &m_gameObjects, &m_textureIDs);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);
    setCallbacks(m_callbacks);
    m_bLoadingComplete = true;
    std::cout << "Entering PauseState\n";
    return true;
}

bool PauseState::onExit(void)
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
    return true;
}

void PauseState::setCallbacks(const std::vector<Callback> &callbacks)
{
    for (unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        if (dynamic_cast<MenuButton *>(m_gameObjects[i]))
        {
            MenuButton *pButton = dynamic_cast<MenuButton *>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void PauseState::s_pauseToMain(void)
{
    std::cout << "going from pause to main\n";
    // Game::Instance()->getGameStateMachine()->changeState(new MainMenuState());
    s_pTransitionState = new MainMenuState();
}

void PauseState::s_resumePlay(void)
{
    Game::Instance()->getGameStateMachine()->popState();
}
