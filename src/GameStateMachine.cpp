#include "GameStateMachine.h"
#include <iostream>

void GameStateMachine::clean()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->onExit();

        delete m_gameStates.back();
        
        m_gameStates.clear();
    }
}

void GameStateMachine::changeState(GameState* pState)
{
    std::cout << "changing states\n";
    if (!m_gameStates.empty())
    {
        if (m_gameStates.back()->getStateID() == pState->getStateID())
        {
            std::cout << "same state\n";
            return;
        }  
        m_gameStates.back()->onExit();
		m_gameStates.pop_back();  
    }
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::pushState(GameState* pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}


void GameStateMachine::popState(void)
{
    if (!m_gameStates.empty())
    {
        m_gameStates.back()->onExit();
        m_gameStates.pop_back();
    }
    m_gameStates.back()->resume();
}

void GameStateMachine::update(void)
{
    // std::cout << "Updating GameStateMachine\n";
    if (!m_gameStates.empty())
    {
        // std::cout << "Not empty GameStateMachine so updating the back\n";
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render(void)
{
    // std::cout << "Rendering GameStateMachine\n";
    if (!m_gameStates.empty())
    {
        // std::cout << "Not empty GameStateMachine so rendering the back\n";
        m_gameStates.back()->render();
    }
}