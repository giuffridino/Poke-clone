#pragma once
#ifndef __GameStateMachine__
#define __GameStateMachine__

#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
	void changeState(GameState* pState);
	void pushState(GameState* pState);
	void popState(void);

    void update(void);
    void render(void);
    void clean();

private:
    std::vector<GameState*> m_gameStates;
    GameState *m_transitionState;
};

#endif /* defined(__GameStateMachine__) */