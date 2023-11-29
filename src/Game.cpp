#include "Game.h"
#include "Player.h"
#include "LoaderParams.h"
#include "MapParser.h"
#include "Map.h"
#include <iostream>
#include "GameObjectFactory.h"
#include "CameraManager.h"
#include "AnimatedObject.h"
#include "GrassObject.h"
#include "InteractableObject.h"
#include "MainMenuState.h"
#include "PlayState.h"

Game *Game::s_pInstance = nullptr;

Game::Game()
{
    m_mapFiles.push_back("first-city.tmx");
	// m_mapFiles.push_back("alien_map2.tmx");
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
    TheGameObjectFactory::Instance()->registerType("GrassObject", new GrassObjectCreator());
    TheGameObjectFactory::Instance()->registerType("InteractableObject", new InteractableObjectCreator());

    // MapParser mapParser;
    // m_pMap = mapParser.parseMap("first-city.tmx");
    m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new PlayState());
	// m_pGameStateMachine->changeState(new MainMenuState());
    
    // TheCameraManager::Instance()->setCameraTarget(m_pMap->getPlayer()->getPosition());
    
    
    return true;
}

void Game::update()
{
    m_pGameStateMachine->update();
    // if(m_pMap != 0)
    // {
    //     m_pMap->update();
    // }
    // TheCameraManager::Instance()->setCameraTarget(m_pMap->getPlayer()->getPosition());
    // for (std::vector<GameObject *>::size_type i = 0; i < m_gameObjects.size(); i++)
	// {
	// 	m_gameObjects[i]->update();
	// }
    // m_player.update();
}

void Game::render()
{
    m_pGameStateMachine->render();
    // if(m_pMap != 0)
    // {
    //     // std::cout << "rendering m_pMap\n";
    //     m_pMap->render();
    // }
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

void Game::clean()
{
    std::cout << "Cleaning game\n";
	m_pGameStateMachine->clean();
	m_pGameStateMachine = 0;
	delete m_pGameStateMachine;
	TheTextureManager::Instance()->clearTextureMap();
}

void Game::quit()
{
    clean();
    CloseWindow();
}