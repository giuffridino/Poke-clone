#pragma once
#ifndef __CollisionManager__
#define __CollisionManager__

// #include "Player.h"
#include "TileLayer.h"
#include <vector>

class GameObject;
class Player;

class CollisionManager
{
public:
    static CollisionManager* Instance(void)
    {
        if (s_pInstance == nullptr)
        {
            s_pInstance = new CollisionManager();
        }
        return s_pInstance;        
    }
    bool checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*> &collisionLayers);
    void checkPlayerRedrawTile(Player* pPlayer, const std::vector<TileLayer*> &redrawLayers);

private:
    CollisionManager(void) {};
    ~CollisionManager(void) {};
    static CollisionManager* s_pInstance;
    Rectangle *getGameObjectRect(GameObject *pGameObject);
    void testCollision(GameObject *pGameObjectA, GameObject *pGameObjectB){};
};

typedef CollisionManager TheCollisionManager;

#endif /* defined(__CollisionManager__) */