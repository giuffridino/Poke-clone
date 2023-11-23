#pragma once
#ifndef __Game__
#define __Game__

#include <raylib.h>
#include <vector>
// #include "Player.h"
#include "GameObject.h"

class Level;

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
    void handleEvents();

    int getGameWidth() { return m_gameWidth; }
    int getGameHeight() { return m_gameHeight; }

private:
    Game();
    static Game* s_pInstance;
    // std::vector<GameObject*> m_gameObjects;
    int m_gameWidth;
	int m_gameHeight;
    // GameObject* m_player;
    // GameObject* m_player2;
    Level* m_pLevel = nullptr;
    // Player m_player;
};

typedef Game TheGame;

#endif /* defined(__Game__) */