#include "CollisionManager.h"
// #include "Collision.h"
#include "GameObject.h"
#include "Player.h"
#include "raymath.h"
#include "DialogManager.h"

CollisionManager* CollisionManager::s_pInstance = nullptr;


bool CollisionManager::checkPlayerTileCollision(Player *pPlayer, const std::vector<TileLayer*> &collisionLayers)
{
    for (std::vector<TileLayer *>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
    {
        TileLayer *pTileLayer = (*it);
        std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();
        int tileColumn, tileRow, tileID = 0;
        if (pPlayer->getFacing() == SOUTH)
        {
            tileColumn = pPlayer->getPosition().x / pTileLayer->getTileSize();
            tileRow = (pPlayer->getPosition().y + 32) / pTileLayer->getTileSize();
            tileID = tiles[tileRow][tileColumn];
        }
        else if (pPlayer->getFacing() == NORTH)
        {
            tileColumn = pPlayer->getPosition().x / pTileLayer->getTileSize();
            tileRow = pPlayer->getPosition().y / pTileLayer->getTileSize();
            tileID = tiles[tileRow][tileColumn];
        }
        else if (pPlayer->getFacing() == EAST)
        {
            tileColumn = (pPlayer->getPosition().x + 16) / pTileLayer->getTileSize();
            tileRow = (pPlayer->getPosition().y + 16) / pTileLayer->getTileSize();
            tileID = tiles[tileRow][tileColumn];
        }
        else if (pPlayer->getFacing() == WEST)
        {
            tileColumn = (pPlayer->getPosition().x - 16) / pTileLayer->getTileSize();
            tileRow = (pPlayer->getPosition().y + 16) / pTileLayer->getTileSize();
            tileID = tiles[tileRow][tileColumn];
        }
        if (tileID != 0)
        {
            // std::cout << "COLLISION\n"; 
            return true;
        }
    }
    return false;
}

bool CollisionManager::checkPlayerInteractableObject(Player* pPlayer, const std::vector<GameObject*> &interactableObjects)
{
    // std::cout << "checkPlayerInteractableObject in CollisionManager\n";
    if (pPlayer->getFacing() == NORTH)
    {
        for (unsigned int i = 0; i < interactableObjects.size(); i++)
        {
            // std::cout << "pPlayer->getPosition(): " << pPlayer->getPosition().x << " " << pPlayer->getPosition().y << "\n";
            // std::cout << "interactableObjects[i]->getPosition(): " << interactableObjects[i]->getPosition().x << " " << interactableObjects[i]->getPosition().y << "\n";
            if (Vector2Equals(pPlayer->getPosition(), {interactableObjects[i]->getPosition().x, interactableObjects[i]->getPosition().y}))
            {
                // TheDialogManager::Instance()->drawDialog();
                return true;
            }
            
        }
    }
    return false;
}

void CollisionManager::checkPlayerRedrawTile(Player* pPlayer, const std::vector<TileLayer*> &redrawLayers)
{
    for (std::vector<TileLayer *>::const_iterator it = redrawLayers.begin(); it != redrawLayers.end(); ++it)
    {
        TileLayer *pTileLayer = (*it);
        std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

        // Vector2 layerPos = pTileLayer->getPosition();

        // int x, y;
        int tileColumn, tileRow, tileID = 0;

        // x = layerPos.x;
        // y = layerPos.y;
        // x = layerPos.x / pTileLayer->getTileSize();
        // y = layerPos.y / pTileLayer->getTileSize();

        tileColumn = (pPlayer->getPosition().x) / pTileLayer->getTileSize();
        tileRow = (pPlayer->getPosition().y + 16) / pTileLayer->getTileSize();
        tileID = tiles[tileRow][tileColumn];
        // std::cout << "pPlayer->getPosition(): " << pPlayer->getPosition().x << " " << pPlayer->getPosition().y << "\n";
        // std::cout << "tileColumn: " << tileColumn << "\n";
        // std::cout << "tileRow: " << tileRow << "\n";
        // std::cout << "tileID: " << tileID << "\n";
        // std::cout << "x: " << x << "\n";
        // std::cout << "y: " << y << "\n";

        if (tileID != 0)
        {
            pTileLayer->renderOneTile(Vector2 {pPlayer->getPosition().x, (pPlayer->getPosition().y + 16)});
            // std::cout << "redraw layer in CollisionManager::checkRedrawTile\n"; 
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