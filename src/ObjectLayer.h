#pragma once
#ifndef __ObjectLayer__
#define __ObjectLayer__

#include "Layer.h"
#include "GameObject.h"
// #include "Map.h"
// #include "CollisionManager.h"
#include <vector>

class Map;

class ObjectLayer : public Layer
{
public:
    virtual ~ObjectLayer();

	virtual void update(Map *pMap);
	virtual void render(Map *pMap);

    void drawGrass();

    std::vector<GameObject*> *getGameObjects(void) { return &m_gameObjects; }
    std::vector<GameObject*> *getInteractableGameObjects(void) { return &m_interactableGameObjects; }
    std::vector<GameObject*> *getGrassObjects(void) { return &m_grassObjects; }

private:
    // CollisionManager m_collisionManager;
    std::vector<GameObject*> m_gameObjects;
    std::vector<GameObject*> m_interactableGameObjects;
    std::vector<GameObject*> m_grassObjects;
};

#endif /* defined(__ObjectLayer__) */