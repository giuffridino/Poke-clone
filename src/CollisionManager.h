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
    void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*> &collisionLayers);

private:
    Rectangle *getGameObjectRect(GameObject *pGameObject);
    void testCollision(GameObject *pGameObjectA, GameObject *pGameObjectB){};
};
#endif /* defined(__CollisionManager__) */