#include "ObjectLayer.h"
#include "Game.h"
#include "Map.h"
#include "CollisionManager.h"
#include "DialogManager.h"
#include <iostream>

ObjectLayer::~ObjectLayer()
{
	for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
        delete (*it);
    }
    m_gameObjects.clear();
}

void ObjectLayer::update(Map *pMap)
{
    // std::cout << "ObjectLayer::update()\n";
	// if(pMap->getPlayer()->getPosition().x + pMap->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth())
	// {
	// 	m_collisionManager.checkPlayerRedrawTile(pMap->getPlayer(), pMap->getRedrawableLayers());
	// 	// m_collisionManager.checkPlayerTileCollision(pMap->getPlayer(), pMap->getCollidableLayers());
	// }
	if (!m_gameObjects.empty())
	{
		for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)
        {
            // std::cout << "ObjectLayer::update()\n";
            (*it)->update();
            if((*it)->type() == std::string("Player"))
            {
                // std::cout << "Checking interaction at player position: " << (*it)->getPosition().x << " " << (*it)->getPosition().y << "\n";
                TheCollisionManager::Instance()->checkPlayerGrassObject(dynamic_cast<Player*>(*it), m_grassObjects);
                // if(TheCollisionManager::Instance()->checkPlayerGrassObject(dynamic_cast<Player*>(*it), m_grassObjects))
                // {
                //     // m_grassObjects[i]->setUpdating(true);
                //     std::cout << "Player in grass detected\n";
                // }
            }
            // if((*it)->type() == std::string("GrassObject") && (*it)->updating())
            // {
            //     (*it)->update();
            // }
            // std::cout << (*it)->type() << "\n";
            // if((*it)->getPosition().x <= TheGame::Instance()->getGameWidth())
            // {
            //     (*it)->setUpdating(true);
            //     (*it)->update();
            // }
            // else
            // {
            //     if((*it)->type() != std::string("Player"))
            //     {
            //         (*it)->setUpdating(false);
            //         // (*it)->scroll(TheGame::Instance()->getGameScrollSpeed());
            //     }
            //     else
            //     {
            //         (*it)->update();
            //     }
            // }
            
            // check if dead or off screen
            if((*it)->getPosition().x < (0 - (*it)->getWidth()) || (*it)->getPosition().y > (TheGame::Instance()->getGameHeight()) || ((*it)->dead()))
            {
                delete *it;
                it = m_gameObjects.erase(it); // erase from vector and get new iterator
            }
            else
            {
                ++it; // increment if all ok
            }
        }
	}
	
    // for (int i = 0; i < m_gameObjects.size(); i++)
	// {
	// 	std::cout << "updating object " << i << "\n";
	// 	m_gameObjects[i]->update();
	// }
}

void ObjectLayer::render(Map *pMap)
{
    // bool drawDialog = false;
	// std::cout << "rendering objectlayer \n";
    for(unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        if(m_gameObjects[i]->getPosition().x <= TheGame::Instance()->getGameWidth())
        {
            // std::cout << "drawing object with ID: " << m_gameObjects[i]->getTextureID() << " in objectlayer at positionX: " << m_gameObjects[i]->getPosition().x << "\n";
            if(m_gameObjects[i]->type() == std::string("Player"))
            {
                // std::cout << "Checking interaction at player position: " << (*it)->getPosition().x << " " << (*it)->getPosition().y << "\n";
                int interactionIdx = TheCollisionManager::Instance()->checkPlayerInteractableObject(dynamic_cast<Player*>(m_gameObjects[i]), m_interactableGameObjects);
                if(interactionIdx != -1)
                {
                    // std::cout << "Interaction detected\n";
                    // std::cout << "m_gameObjects[i]->getInteractionText(): " << m_gameObjects[i]->getInteractionText() << "\n";
                    TheDialogManager::Instance()->drawDialogLater(m_interactableGameObjects[interactionIdx]->getInteractionText());
                    // drawDialog = true;
                    
                }
                else
                {
                    TheDialogManager::Instance()->resetDialogVariables();
                }
                
            }
            m_gameObjects[i]->draw();
        }
    }
    // if(drawDialog)
    // {
    //     TheDialogManager::Instance()->drawDialog();
    // }
    // if(pMap->getPlayer()->getPosition().x + pMap->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth())
	// {
	// 	m_collisionManager.checkPlayerRedrawTile(pMap->getPlayer(), pMap->getRedrawableLayers());
	// 	// m_collisionManager.checkPlayerTileCollision(pMap->getPlayer(), pMap->getCollidableLayers());
	// }
}

void ObjectLayer::drawGrass()
{
    for(std::vector<GameObject*>::iterator it = m_grassObjects.begin(); it != m_grassObjects.end();)
    {
        std::cout << "drawing grass\n";
        (*it)->draw();
        ++it;
    }
}