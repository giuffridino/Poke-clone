#pragma once
#ifndef __GameStates__
#define __GameStates__

#include <string>
#include <vector>
#include "TextureManager.h"
#include "GameObject.h"

class GameState 
{
public:
	virtual ~GameState(){ }
	virtual std::string getStateID() const = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual void resume() {}
protected:
	GameState() : m_bLoadingComplete(false), m_bExiting(false)
	{
	}
	std::vector<std::string> m_textureIDs;
	bool m_bLoadingComplete;
	bool m_bExiting;
};

#endif /* defined(__GameStates__) */