#include "ObjectLayer.h"
#include "Game.h"
#include "Level.h"
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

void ObjectLayer::update(Level *pLevel)
{
    // std::cout << "ObjectLayer::update()\n";
	// if(pLevel->getPlayer()->getPosition().x + pLevel->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth())
	// {
	// 	m_collisionManager.checkPlayerRedrawTile(pLevel->getPlayer(), pLevel->getRedrawableLayers());
	// 	// m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());
	// }
	if (!m_gameObjects.empty())
	{
		for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)
        {
            // std::cout << "ObjectLayer::update()\n";
            (*it)->update();
            // if((*it)->type() == std::string("Player"))
            // {
            //     // std::cout << "Checking interaction at player position: " << (*it)->getPosition().x << " " << (*it)->getPosition().y << "\n";
            //     if(TheCollisionManager::Instance()->checkPlayerInteractableObject(dynamic_cast<Player*>(*it), m_interactableGameObjects))
            //     {
            //         std::cout << "Interaction detected\n";
            //     }
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

void ObjectLayer::render(Level *pLevel)
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
                if(TheCollisionManager::Instance()->checkPlayerInteractableObject(dynamic_cast<Player*>(m_gameObjects[i]), m_interactableGameObjects))
                {
                    std::cout << "Interaction detected\n";
                    TheDialogManager::Instance()->drawDialogLater(std::string("Hello poke-clone"));
                    // drawDialog = true;
                    
                }
            }
            m_gameObjects[i]->draw();
        }
    }
    // if(drawDialog)
    // {
    //     TheDialogManager::Instance()->drawDialog();
    // }
    // if(pLevel->getPlayer()->getPosition().x + pLevel->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth())
	// {
	// 	m_collisionManager.checkPlayerRedrawTile(pLevel->getPlayer(), pLevel->getRedrawableLayers());
	// 	// m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());
	// }
}