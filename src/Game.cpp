#include "Game.h"
#include "Player.h"
#include "LoaderParams.h"
#include "LevelParser.h"
#include "Level.h"
#include <iostream>
#include "GameObjectFactory.h"
#include "CameraManager.h"
#include "AnimatedObject.h"
#include "InteractableObject.h"

Game *Game::s_pInstance = nullptr;

Game::Game()
{

}

bool Game::init(const char *title, int width, int height)
{
    InitWindow(width, height, "Poke-Clone");
    m_gameWidth = width;
	m_gameHeight = height;
    SetTargetFPS(60);

    // m_player = new Player();
    // m_player->load(std::unique_ptr<LoaderParams>( new LoaderParams("main-trainer", Vector2{0.0f, 0.0f}, 16, 32, 0, 0, 4, 0, 10, SOUTH)));
    // m_player2->load(std::unique_ptr<LoaderParams>( new LoaderParams("main-trainer", Vector2{0.0f, 0.0f}, 16, 32, 0, 0, 4, 0, 10, SOUTH)));
    // m_gameObjects.push_back(m_player);
    // m_gameObjects.push_back(m_player2);

    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedObject", new AnimatedObjectCreator());
    TheGameObjectFactory::Instance()->registerType("InteractableObject", new InteractableObjectCreator());

    LevelParser levelParser;
    m_pLevel = levelParser.parseLevel("first-city.tmx");
    
    TheCameraManager::Instance()->setCameraTarget(m_pLevel->getPlayer()->getPosition());
    
    
    return true;
}

void Game::update()
{
    if(m_pLevel != 0)
    {
        m_pLevel->update();
    }
    TheCameraManager::Instance()->setCameraTarget(m_pLevel->getPlayer()->getPosition());
    // for (std::vector<GameObject *>::size_type i = 0; i < m_gameObjects.size(); i++)
	// {
	// 	m_gameObjects[i]->update();
	// }
    // m_player.update();
}

void Game::render()
{
    if(m_pLevel != 0)
    {
        // std::cout << "rendering m_pLevel\n";
        m_pLevel->render();
    }
    // for (std::vector<GameObject *>::size_type i = 0; i < m_gameObjects.size(); i++)
	// {
	// 	m_gameObjects[i]->draw();
	// }
    // m_player.draw();
}

void Game::handleEvents()
{

}

bool Game::running()
{
    return !WindowShouldClose();
}