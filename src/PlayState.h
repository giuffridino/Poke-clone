#pragma once
#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"
// #include "GameObject.h"
#include <string>
#include <vector>

class ShooterObject;

class Map;

class PlayState : public GameState
{
public:
	virtual ~PlayState(void);

	virtual void update(void);
	virtual void render(void);

	virtual bool onEnter(void);
	virtual bool onExit(void);

	virtual std::string getStateID(void) const { return s_playID; };

private:
    static const std::string s_playID;

	std::vector<GameObject*> m_gameObjects;

	Map* m_pMap;
};

#endif /* defined(__PlayState__) */