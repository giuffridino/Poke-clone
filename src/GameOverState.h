#pragma once
#ifndef __GameOverState__
#define __GameOverState__

#include "MenuState.h"
#include "GameObject.h"
#include <string>
#include <vector>

class GameOverState : public MenuState
{
public:
	GameOverState() {};

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_gameOverID; };

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
    static void s_gameOverToMain();
    static void s_restartPlay();
	static GameState *s_pTransitionState;

    static const std::string s_gameOverID;

	std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__GameOverState__) */