#include "MainMenuState.h"
#include "PlayState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "LoaderParams.h"
#include "StateParser.h"
#include "MenuButton.h"

const std::string MainMenuState::s_mainMenuID = "MENU";

void MainMenuState::update()
{
    std::cout << "MainMenuState::update()\n";
    if (m_bLoadingComplete && !m_gameObjects.empty())
    {
        for (unsigned int i = 0; i < m_gameObjects.size(); i++)
        {
            if (m_gameObjects[i])
            {
                m_gameObjects[i]->update();
            }
        }
    }
}

void MainMenuState::render()
{
    std::cout << "MainMenuState::render()\n";
    if (m_bLoadingComplete && !m_gameObjects.empty())
    {
        for (unsigned int i = 0; i < m_gameObjects.size(); i++)
        {
            if (m_gameObjects[i])
            {
                std::cout << "Trying to draw m_gameObjects[i] in MainMenuStateRender()\n";
                m_gameObjects[i]->draw();
            }
        }
    }
}

bool MainMenuState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("assets/attack.xml", s_mainMenuID, &m_gameObjects, &m_textureIDs);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);
    setCallbacks(m_callbacks);
    m_bLoadingComplete = true;
    std::cout << "Entering MainMenuState\n";
    return true;
}

bool MainMenuState::onExit()
{
    m_bExiting = true;
    if (m_bLoadingComplete && !m_gameObjects.empty())
    {
        for (unsigned int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->clean();
            m_gameObjects.pop_back();
        }
        m_gameObjects.clear();
    }
    for (unsigned int i = 0; i < m_textureIDs.size(); i++)
    {
        TextureManager::Instance()->unload(m_textureIDs[i]);
    }
    // TheInputHandler::Instance()->reset();

    std::cout << "exiting MainMenuState\n";
    return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    if (!m_gameObjects.empty())
    {
        for (unsigned int i = 0; i < m_gameObjects.size(); i++)
        {
            if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
            {
                MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
                pButton->setCallback(callbacks[pButton->getCallbackID()]);
                std::cout << "Setting callback for MenuButton for which pButton->getCallbackID() = " << pButton->getCallbackID() << "\n";
                std::cout << "Setting callback for MenuButton for which callbacks[pButton->getCallbackID()] = " << callbacks[pButton->getCallbackID()] << "\n";
            }
        }
    }
}

void MainMenuState::s_menuToPlay()
{
    std::cout << "Play button clicked\n";
    // s_pTransitionState = new PlayState();
    Game::Instance()->getGameStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    std::cout << "Exit button clicked\n";
    // TheGame::Instance()->getGameStateMachine()->popState();
    Game::Instance()->quit();
}
