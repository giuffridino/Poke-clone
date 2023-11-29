#pragma once
#ifndef __Game__
#define __Game__

#include <raylib.h>
#include <vector>
// #include "Player.h"
#include "GameObject.h"
#include "GameStateMachine.h"

class Map;

class Game
{
public:
    static Game* Instance(void)
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Game();
		}
		return s_pInstance;
	}
    ~Game(){};
    bool init(const char *title, int width, int height);
    bool running();
    void update();
    void render();
    void clean();
    void handleEvents();

    int getGameWidth() { return m_gameWidth; }
    int getGameHeight() { return m_gameHeight; }
    GameStateMachine* getGameStateMachine(void) { return m_pGameStateMachine; }
    void setCurrentMap(int map) { m_currentMap = map; }
	const int getCurrentMap(void) { return m_currentMap; }
    std::vector<std::string> getMapFiles() { return m_mapFiles; }

    void quit();

private:
    Game();
    static Game* s_pInstance;
    int m_gameWidth;
	int m_gameHeight;
    Map* m_pMap = nullptr;
    int m_currentMap = 0;
    std::vector<std::string> m_mapFiles;
    GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;

#endif /* defined(__Game__) */