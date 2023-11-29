#pragma once
#ifndef __PauseState__
#define __PauseState__

#include "GameState.h"
#include "GameObject.h"
#include "MenuState.h"
#include <string>
#include <vector>


class PauseState : public MenuState
{
public:
	PauseState() {};

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; };


private:
	static void s_pauseToMain();
	static void s_resumePlay();
	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static GameState *s_pTransitionState;

    static const std::string s_pauseID;

	std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__PauseState__) */