#pragma once
#ifndef __ObjectLayer__
#define __ObjectLayer__

#include "Layer.h"
#include "GameObject.h"
#include "Level.h"
#include <vector>

class ObjectLayer : public Layer
{
public:
    virtual ~ObjectLayer();

	virtual void update(Level *pLevel);
	virtual void render(void);

    std::vector<GameObject*> *getGameObjects(void) { return &m_gameObjects; }

private:
    std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__ObjectLayer__) */