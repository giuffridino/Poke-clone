#pragma once
#ifndef __ObjectLayer__
#define __ObjectLayer__

#include "Layer.h"
#include "GameObject.h"
// #include "Level.h"
// #include "CollisionManager.h"
#include <vector>

class Level;

class ObjectLayer : public Layer
{
public:
    virtual ~ObjectLayer();

	virtual void update(Level *pLevel);
	virtual void render(Level *pLevel);

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