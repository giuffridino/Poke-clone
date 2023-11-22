#include "CollisionManager.h"
// #include "Collision.h"
#include "GameObject.h"
#include "Player.h"

void CollisionManager::checkPlayerTileCollision(Player *pPlayer, const std::vector<TileLayer*> &collisionLayers)
{
    for (std::vector<TileLayer *>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
    {
        TileLayer *pTileLayer = (*it);
        std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

        Vector2 layerPos = pTileLayer->getPosition();

        int x, y, tileColumn, tileRow, tileID = 0;

        // x = layerPos.x;
        // y = layerPos.y;
        x = layerPos.x / pTileLayer->getTileSize();
        y = layerPos.y / pTileLayer->getTileSize();

        if (pPlayer->getFacing() == EAST)
        {
            tileColumn = ((pPlayer->getPosition().x + pPlayer->getWidth() + 8) / pTileLayer->getTileSize());
            tileRow = ((pPlayer->getPosition().y + 8) / pTileLayer->getTileSize());
            tileID = tiles[tileRow + y][tileColumn + x];
        }
        else if (pPlayer->getFacing() == WEST)
        {
            tileColumn = ((pPlayer->getPosition().x - 8) / pTileLayer->getTileSize());
            tileRow = ((pPlayer->getPosition().y + 8) / pTileLayer->getTileSize());
            tileID = tiles[tileRow + y][tileColumn + x];
        }
        else if (pPlayer->getFacing() == NORTH)
        {
            tileColumn = ((pPlayer->getPosition().x - 8) / pTileLayer->getTileSize());
            tileRow = ((pPlayer->getPosition().y - 8) / pTileLayer->getTileSize());
            tileID = tiles[tileRow + y][tileColumn + x];
        }
        else if (pPlayer->getFacing() == SOUTH)
        {
            tileColumn = ((pPlayer->getPosition().x + 8) / pTileLayer->getTileSize());
            tileRow = ((pPlayer->getPosition().y + pPlayer->getHeight() + 8) / pTileLayer->getTileSize());
            tileID = tiles[tileRow + y][tileColumn + x];
        }

        if (tileID != 0)
        {
            pPlayer->collision();
            // std::cout << "collision in CollisionManager::checkPlayerTileCollision\n"; 
        }
        
    }
}

Rectangle *CollisionManager::getGameObjectRect(GameObject *pGameObject)
{
    Rectangle *pRect = new Rectangle();
    pRect->x = pGameObject->getPosition().x;
    pRect->y = pGameObject->getPosition().y;
    pRect->width = pGameObject->getWidth();
    pRect->height = pGameObject->getHeight();
    return pRect;
}

// void CollisionManager::testCollision(GameObject *pGameObjectA, GameObject *pGameObjectB)
// {
//     Rectangle *pRectA = getGameObjectRect(pGameObjectA);
//     Rectangle *pRectB = getGameObjectRect(pGameObjectB);
//     if (RectRect(pRectA, pRectB))
//     {
//         if (!pGameObjectA->dying() && !pGameObjectB->dying())
//         {
//             pGameObjectA->collision();
//             pGameObjectB->collision();
//         }
//     }
//     delete pRectA;
//     delete pRectB;
// }